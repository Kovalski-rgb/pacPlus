#include <vector>
#include <stdio.h>
#include <cmath>
#include <ncurses.h>
#include <chrono>
#include "pacman.h"
#include "gameScreen.h"
#include "randomPath.h"
#include "ghost.h"

using namespace std;

class Game{
    public:

    bool gameEnded;
    Screen screen;
    vector<vector<int>> gameMap;
    
    Pacman player;
    Ghost blinky;
    Ghost pinky;
    Ghost inky;
    Ghost clyde;

    string fontColor;
    string bgColor;
    char columnSeparator;
    int score;
    int pellets;
    vector<IEntity*> entityList;
    vector<Ghost*> ghostList;
    IPathFinder* ai;

    chrono::_V2::system_clock::time_point fpsTimer;
    chrono::_V2::system_clock::time_point refreshTimer;
    chrono::_V2::system_clock::time_point movementTimer;
    chrono::_V2::system_clock::time_point globalTimer;

    int iterationCounter;
    int fps;
    int fpsCap;
    int movementCap;

    Game(Screen screen){
        this->gameEnded = false;
        this->gameMap = screen.setupGameField();
        this->pellets = screen.countPellets(gameMap);
        this->player = Pacman(25,13);
        this->columnSeparator = ' ';
        this->score = 0;
        this->ai = new RandomPath();
        this->fps = 0;
        this->fpsCap = 50; //50=~20fps, 33=30fps, 16=~60fps
        this->movementCap = 10;

        this->blinky = Ghost(16, 11, 66, COLOR_BLACK, COLOR_RED);
        this->pinky = Ghost(16, 12, 80, COLOR_BLACK, COLOR_MAGENTA);
        this->inky = Ghost(16, 15, 73, COLOR_BLACK, COLOR_CYAN);
        this->clyde = Ghost(16, 16, 99, COLOR_BLACK, COLOR_GREEN);

        this->ghostList = { &blinky, &pinky, &inky, &clyde };
        this->entityList = { &player, &blinky, &pinky, &inky, &clyde };
    }

    void play(){
        initscr();
        keypad(stdscr, TRUE);	
        raw();
        start_color();
        
        init_pair(0, COLOR_BLACK, COLOR_WHITE);

        printMap();
        printPlayer();
        globalTimer = chrono::high_resolution_clock::now();
        preGame();
        movementTimer = chrono::high_resolution_clock::now();
        refreshTimer = chrono::high_resolution_clock::now();

        while(!gameEnded){
            keyPressHandler();

            auto movementNow = chrono::high_resolution_clock::now();
            auto movementDiff = chrono::duration_cast<chrono::milliseconds>(movementNow - movementTimer).count();

            // limit to update player movement
            if(movementDiff >= movementCap){
                movementTimer = chrono::high_resolution_clock::now();
                                
                for(int index = 0; index < ghostList.size(); index++){
                    auto movement = ghostList[index]->nextPath();
                    ghostList[index]->setAxisY(movement[0]);
                    ghostList[index]->setAxisX(movement[1]);

                    vector<double> nextExpectedPos = getNextEntityPos(ghostList[index]);
                    if(isValidGhostMove(nextExpectedPos, ghostList[index]))
                    {
                        moveEntity(ghostList[index]);
                    }
                }

                vector<double> nextExpectedPos = getNextEntityPos(&player);
                if(isValidPlayerMove(nextExpectedPos, &player))
                {
                    processNextMoveScore(nextExpectedPos[0], nextExpectedPos[1]);
                    moveEntity(&player);
                }
            }

            // limit to refreshRate
            auto refreshNow = chrono::high_resolution_clock::now();
            auto refreshDiff = chrono::duration_cast<chrono::milliseconds>(refreshNow - refreshTimer).count();
            if(refreshDiff >= fpsCap){
                refreshTimer = chrono::high_resolution_clock::now();
                refreshScreen();
            }

            if(pellets == 0){
                resetMap();
            }

        }
        endwin();
    }

    void refreshScreen(){
        printMap();
        printEntities();
        printDebug(3, "Player Pos["+to_string(player.getPosY())+"]["+to_string(player.getPosX())+"]");
        printDebug(4, "Score: "+to_string(score));
        printDebug(5, "PelletCount: "+to_string(pellets));

        auto now = chrono::high_resolution_clock::now();
        long diff = chrono::duration_cast<chrono::milliseconds>(now-fpsTimer).count();

        printDebug(8, "Player front Pos ("+to_string(gameMap[player.getPosY()+1*player.getAxisY()][player.getPosX()+1*player.getAxisX()])+") ["+to_string(player.getPosY()+1*player.getAxisY())+"]["+to_string(player.getPosX()+1*player.getAxisX())+"]");
        printDebug(6, "Fps: "+ to_string(fps) + "fps");


        vector<double> nextExpectedPos = getNextEntityPos(&player);
        printDebug(9, "Is next pos valid? "+to_string(isValidPlayerMove(nextExpectedPos, &player)));

        if(diff>=1000){
            fps = iterationCounter;
            iterationCounter = 0;
            fpsTimer = chrono::high_resolution_clock::now();
        }else{
            iterationCounter++; 
        }
    }

    bool isValidGhostMove(vector<double> nextExpectedPos, IEntity* entity){
        return (gameMap[floor(nextExpectedPos[0])][floor(nextExpectedPos[1])] == entity->getAppearance() ||
                gameMap[floor(nextExpectedPos[0])][floor(nextExpectedPos[1])] == screen.BLANK_SPACE ||
                gameMap[floor(nextExpectedPos[0])][floor(nextExpectedPos[1])] == screen.PELLET ||
                (floor(nextExpectedPos[0]) == 16 && floor(nextExpectedPos[1]) == -1)  ||
                (floor(nextExpectedPos[0]) == 16 && floor(nextExpectedPos[1]) == 28)  ||
                gameMap[floor(nextExpectedPos[0])][floor(nextExpectedPos[1])] == screen.POWER_PELLET|| 
                gameMap[floor(nextExpectedPos[0])][floor(nextExpectedPos[1])] == screen.GHOST_GATE);
    }

    bool isValidPlayerMove(vector<double> nextExpectedPos, IEntity* entity){
        return (gameMap[floor(nextExpectedPos[0])][floor(nextExpectedPos[1])] == entity->getAppearance() ||
                gameMap[floor(nextExpectedPos[0])][floor(nextExpectedPos[1])] == screen.BLANK_SPACE ||
                gameMap[floor(nextExpectedPos[0])][floor(nextExpectedPos[1])] == screen.PELLET || 
                (floor(nextExpectedPos[0]) == 16 && floor(nextExpectedPos[1]) == -1)  ||
                (floor(nextExpectedPos[0]) == 16 && floor(nextExpectedPos[1]) == 28)  ||
                gameMap[floor(nextExpectedPos[0])][floor(nextExpectedPos[1])] == screen.POWER_PELLET);
    }

    void preGame(){
        int count = 4;
        while(count>0){
            auto now = chrono::high_resolution_clock::now();
            long diff = chrono::duration_cast<chrono::milliseconds>(now-fpsTimer).count();

            if(diff>=1000){
                count--;
                fpsTimer = chrono::high_resolution_clock::now();
            }
            printDebug(7, to_string(count));
        }

    }

    void player_ia(){
        vector<Axis> movement = ai->turnDirection();
        player.setAxisY(movement[0]);
        player.setAxisX(movement[1]);
    }

    void resetMap(){
        player.setPosX(player.getInitPosX());
        player.setPosY(player.getInitPosY());
        gameMap = screen.setupGameField();
        pellets = screen.countPellets(gameMap);

        for(int index = 0; index < ghostList.size(); index++){
            ghostList[index]->setPosX(ghostList[index]->getInitPosX());
            ghostList[index]->setPosY(ghostList[index]->getInitPosY());
        }
    }

    void processNextMoveScore(int posY, int posX){
        if(gameMap[posY][posX] == screen.PELLET){
            gameMap[posY][posX] = screen.BLANK_SPACE;
            pellets -= 1;
            score += 10;
            return;
        }
        if(gameMap[posY][posX] == screen.POWER_PELLET){
            gameMap[posY][posX] = screen.BLANK_SPACE;
            score += 50;
            return;
        }
    }

    vector<double> getEntityDeltas(IEntity* entity){
        vector<double> deltas(2, 0);

        deltas[0] = entity->getAxisY()*entity->getSpeed();
        deltas[1] = entity->getAxisX()*entity->getSpeed();
        
        return deltas;
    }

    vector<double> getNextEntityPos(IEntity* entity){
        vector<double> pos(2, 0);
        vector<double> deltas = getEntityDeltas(entity);

        pos[0] = entity->getPosY()+deltas[0];
        pos[1] = entity->getPosX()+deltas[1];
        
        return pos;
    }

    void printDebug(int line, char message){
        int row,col;
        getmaxyx(stdscr,row,col);

        int spacer = gameMap[0].size()*2 + 3;
        mvprintw(line, spacer, "%c", message); 


        mvprintw(row-1, col-1, " ");
        refresh();
    }

    void printDebug(int line, char *message){
        int row,col;
        getmaxyx(stdscr,row,col);

        int spacer = gameMap[0].size()*2 + 3;
        mvprintw(line, spacer, message); 


        mvprintw(row-1, col-1, " ");
        refresh();
    }

    void printDebug(int line, string message){
        int row,col;
        getmaxyx(stdscr,row,col);

        int spacer = gameMap[0].size()*2 + 3;
        mvprintw(line, spacer, message.c_str()); 


        mvprintw(row-1, col-1, " ");
        refresh();
    }

    void moveEntity(IEntity* entity){
        vector<double> nextPos = getNextEntityPos(entity);

        if(floor(nextPos[0]) == 16 && floor(nextPos[1]) ==-1){
            entity->setPosY(16);
            entity->setPosX(27);    
        }else if(floor(nextPos[0]) == 16 && floor(nextPos[1]) ==28){
            entity->setPosY(16);
            entity->setPosX(0);    
        } else {
            entity->setPosY(nextPos[0]);
            entity->setPosX(nextPos[1]);
        }
    }

    // can be optimized to just print the diff, not the entire map (maybe ncurses already does that, idk)
    void printMap(){
        int row,col;
        getmaxyx(stdscr,row,col);

        init_pair(1, COLOR_BLUE, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, COLOR_BLACK);

        move(0,0);
        for (long unsigned int row = 0; row < gameMap.size(); row++){
            for(long unsigned int col = 0; col < gameMap[0].size(); col++){
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(1));
                if(gameMap[row][col] == screen.PELLET || gameMap[row][col] == screen.POWER_PELLET){
                    attroff(COLOR_PAIR(1));
                    attron(COLOR_PAIR(2));    
                }
                printw("%c%c", (char) gameMap[row][col], (char) columnSeparator);
            }
            printw("\n");
        }
        mvprintw(row-1, col-1, " ");
        refresh();
    }

    void printPlayer(){
        int row,col;
        getmaxyx(stdscr,row,col);
        init_pair(3, COLOR_BLACK, COLOR_YELLOW);

        attron(COLOR_PAIR(3)); 
        mvprintw(floor(player.getPosY()), floor(player.getPosX())*2, "%c", (char)player.getAppearance());
        attroff(COLOR_PAIR(3));
        mvprintw(row-1, col-1, " ");

        refresh();
    }

    void printEntities(){
        int row,col;
        getmaxyx(stdscr,row,col);

        for(int index = 0; index < entityList.size(); index++){
            init_pair(30+index, entityList[index]->getColor(), entityList[index]->getBackground());

            attron(COLOR_PAIR(30+index)); 
            mvprintw(floor(entityList[index]->getPosY()), floor(entityList[index]->getPosX())*2, "%c", (char)entityList[index]->getAppearance());
            attroff(COLOR_PAIR(30+index));
            mvprintw(row-1, col-1, " ");

            refresh();
        }
    }

    void keyPressHandler(){
        int key;
        timeout(0);
        key = getch();

        switch(key){
            case KEY_UP:
            if(gameMap[floor(player.getPosY()-1)][floor(player.getPosX())] == screen.BLANK_SPACE ||
                gameMap[floor(player.getPosY()-1)][floor(player.getPosX())] == screen.PELLET || 
                gameMap[floor(player.getPosY()-1)][floor(player.getPosX())] == screen.POWER_PELLET)
                {
                    player.setAxisY(down);
                    player.setAxisX(neutral);
                }
            break;

            case KEY_DOWN:
            if(gameMap[floor(player.getPosY()+1)][floor(player.getPosX())] == screen.BLANK_SPACE ||
                gameMap[floor(player.getPosY()+1)][floor(player.getPosX())] == screen.PELLET || 
                gameMap[floor(player.getPosY()+1)][floor(player.getPosX())] == screen.POWER_PELLET)
                {
                    player.setAxisY(up);
                    player.setAxisX(neutral);
                }
            break;

            case KEY_LEFT:
            if(gameMap[floor(player.getPosY())][floor(player.getPosX()-1)] == screen.BLANK_SPACE ||
                gameMap[floor(player.getPosY())][floor(player.getPosX()-1)] == screen.PELLET || 
                gameMap[floor(player.getPosY())][floor(player.getPosX()-1)] == screen.POWER_PELLET)
                {
                    player.setAxisY(neutral);
                    player.setAxisX(down);
                }
            break;

            case KEY_RIGHT:
            if(gameMap[floor(player.getPosY())][floor(player.getPosX()+1)] == screen.BLANK_SPACE ||
                gameMap[floor(player.getPosY())][floor(player.getPosX()+1)] == screen.PELLET || 
                gameMap[floor(player.getPosY())][floor(player.getPosX()+1)] == screen.POWER_PELLET)
                {
                    player.setAxisY(neutral);
                    player.setAxisX(up);
                }
            break;

            case 27:
                gameEnded = true;
            break;
        }
    }
};