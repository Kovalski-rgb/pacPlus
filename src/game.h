#include <vector>
#include <stdio.h>
#include <cmath>
#include <ncurses.h>
#include "pacman.h"
#include "gameScreen.h"

using namespace std;

class Game{
    public:

    bool gameEnded;
    Screen screen;
    vector<vector<int>> gameMap;
    Pacman player;
    string fontColor;
    string bgColor;
    char columnSeparator;

    Game(Screen screen){
        this->gameEnded = false;
        this->gameMap = screen.map;
        this->player = Pacman(25,13);
        this->columnSeparator = ' ';
    }

    void play(){
        initscr();
        keypad(stdscr, TRUE);	
        raw();
        start_color();
        
        init_pair(0, COLOR_BLACK, COLOR_WHITE);

        while(!gameEnded){
            keyPressHandler();
            vector<double> nextExpectedPos = getNextPlayerPos();

            if(
                gameMap[floor(nextExpectedPos[0])][floor(nextExpectedPos[1])] == player.getAppearance() ||
                gameMap[floor(nextExpectedPos[0])][floor(nextExpectedPos[1])] == screen.BLANK_SPACE ||
                gameMap[floor(nextExpectedPos[0])][floor(nextExpectedPos[1])] == screen.PELLET || 
                gameMap[floor(nextExpectedPos[0])][floor(nextExpectedPos[1])] == screen.POWER_PELLET)
            {
                movePlayer();
            }
            printMap();
            printEntities();
            printDebug(3, "Player Pos["+to_string(player.getPosY())+"]["+to_string(player.getPosX())+"]");
        }
        endwin();
    }

    vector<double> getPlayerDeltas(){
        vector<double> deltas(2, 0);

        deltas[0] = player.getAxisY()*player.getSpeed();
        deltas[1] = player.getAxisX()*player.getSpeed();
        
        return deltas;
    }

    vector<double> getNextPlayerPos(){
        vector<double> pos(2, 0);
        vector<double> deltas = getPlayerDeltas();

        pos[0] = player.getPosY()+deltas[0];
        pos[1] = player.getPosX()+deltas[1];
        
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

    void movePlayer(){
        vector<double> nextPos = getNextPlayerPos();

        player.setPosY(nextPos[0]);
        player.setPosX(nextPos[1]);
    }

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

    void printEntities(){
        int row,col;
        getmaxyx(stdscr,row,col);
        init_pair(3, COLOR_BLACK, COLOR_YELLOW);

        attron(COLOR_PAIR(3)); 
        mvprintw(floor(player.getPosY()), floor(player.getPosX())*2, "%c", (char)player.getAppearance());
        attroff(COLOR_PAIR(3));
        mvprintw(row-1, col-1, " ");

        refresh();
    }

    void keyPressHandler(){
        int key;
        timeout(10);
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