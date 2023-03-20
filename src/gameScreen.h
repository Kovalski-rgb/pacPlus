#include <vector>
#include <iostream>
#include <string>

using namespace std;

vector<vector<int>> screen;
int SCREEN_MARGIN_TOP, SCREEN_MARGIN_BOTTOM;
int SCREEN_HEIGHT, SCREEN_WIDTH, HALF_SCREEN_HEIGHT, HALF_SCREEN_WIDTH;

// interactable objects inside field
int POWER_PELLET,
    PELLET;

// walls and CLI interface values
int BLANK_SPACE;
int HORIZONTAL_WALL;
int VERTICAL_WALL;
int DIAGONAL_LEFT;
int DIAGONAL_RIGHT;
int INNER_DIAGONAL;
int GHOST_GATE;

// colors
string BG_BLACK;
string BG_RED;
string BG_GREEN;
string BG_YELLOW;
string BG_BLUE;
string BG_MAGENTA;
string BG_CYAN;
string BG_WHITE;

string F_BLACK;
string F_RED;
string F_GREEN;
string F_YELLOW;
string F_BLUE;
string F_MAGENTA;
string F_CYAN;
string F_WHITE;

string BG_F_RESET;

// the purpose of these variables is just to instantiate the game screen, they are the same as the verbose ones

// [ ] - blank space 
int bs;
// [-] - horizontal wall 
int hw;
// [|] - vertical wall
int vw;
// [\\] - diagonal left 
int dl;
// [/] - diagonal right
int dr;
// [*] - pellet
int pl;
// [o] - power pellet
int pp;
// [=] - ghost gate
int gg;
// [+] - inner diagonal
int id;

void setupGameVariables(){
    SCREEN_HEIGHT = 36;
    SCREEN_WIDTH = 28;

    HALF_SCREEN_WIDTH = SCREEN_WIDTH/2;
    HALF_SCREEN_HEIGHT = SCREEN_HEIGHT/2;

    POWER_PELLET = 64;//111;
    PELLET = 42;

    BLANK_SPACE = 32;
    HORIZONTAL_WALL = 45;
    VERTICAL_WALL = 124;
    DIAGONAL_LEFT = 92;
    DIAGONAL_RIGHT = 47;
    SCREEN_MARGIN_TOP = 2; 
    SCREEN_MARGIN_BOTTOM = 1;
    GHOST_GATE = 61;
    INNER_DIAGONAL = 43;

    bs = BLANK_SPACE;
    hw = HORIZONTAL_WALL;
    vw = VERTICAL_WALL;
    dl = DIAGONAL_LEFT;
    dr = DIAGONAL_RIGHT;
    pp = POWER_PELLET;
    pl = PELLET;
    gg = GHOST_GATE;
    id = INNER_DIAGONAL;

    BG_BLACK   = "\033[40m";
    BG_RED     = "\033[41m";
    BG_GREEN   = "\033[42m";
    BG_YELLOW  = "\033[43m";
    BG_BLUE    = "\033[44m";
    BG_MAGENTA = "\033[45m";
    BG_CYAN    = "\033[46m";
    BG_WHITE   = "\033[47m";

    F_BLACK    = "\033[30m";
    F_RED      = "\033[31m";
    F_GREEN    = "\033[32m";
    F_YELLOW   = "\033[33m";
    F_BLUE     = "\033[34m";
    F_MAGENTA  = "\033[35m";
    F_CYAN     = "\033[36m";
    F_WHITE    = "\033[37m";

    BG_F_RESET = "\033[0m";

    vector<vector<int>> screen(SCREEN_HEIGHT, vector(SCREEN_WIDTH, BLANK_SPACE));
    ::screen = screen;
}

void setupGameField(){
    vector<vector<int>> screen
    {                                           //|
        {bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs},
        {bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs},
        {dr,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,dl,dr,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,dl},
        {vw,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,vw,vw,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,vw},
        {vw,pl,dr,hw,hw,dl,pl,dr,hw,hw,hw,dl,pl,vw,vw,pl,dr,hw,hw,hw,dl,pl,dr,hw,hw,dl,pl,vw},
        {vw,pp,vw,bs,bs,vw,pl,vw,bs,bs,bs,vw,pl,vw,vw,pl,vw,bs,bs,bs,vw,pl,vw,bs,bs,vw,pp,vw},
        {vw,pl,dl,hw,hw,dr,pl,dl,hw,hw,hw,dr,pl,dl,dr,pl,dl,hw,hw,hw,dr,pl,dl,hw,hw,dr,pl,vw},
        {vw,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,vw},
        {vw,pl,dr,hw,hw,dl,pl,dr,dl,pl,dr,hw,hw,hw,hw,hw,hw,dl,pl,dr,dl,pl,dr,hw,hw,dl,pl,vw},
        {vw,pl,dl,hw,hw,dr,pl,vw,vw,pl,dl,hw,hw,id,id,hw,hw,dr,pl,vw,vw,pl,dl,hw,hw,dr,pl,vw},
        {vw,pl,pl,pl,pl,pl,pl,vw,vw,pl,pl,pl,pl,vw,vw,pl,pl,pl,pl,vw,vw,pl,pl,pl,pl,pl,pl,vw},
        {dl,hw,hw,hw,hw,dl,pl,vw,id,hw,hw,dl,bs,vw,vw,bs,dr,hw,hw,id,vw,pl,dr,hw,hw,hw,hw,dr},
        {bs,bs,bs,bs,bs,vw,pl,vw,id,hw,hw,dr,bs,dl,dr,bs,dl,hw,hw,id,vw,pl,vw,bs,bs,bs,bs,bs},
        {bs,bs,bs,bs,bs,vw,pl,vw,vw,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,vw,vw,pl,vw,bs,bs,bs,bs,bs},
        {bs,bs,bs,bs,bs,vw,pl,vw,vw,bs,dr,hw,hw,gg,gg,hw,hw,dl,bs,vw,vw,pl,vw,bs,bs,bs,bs,bs},
        {hw,hw,hw,hw,hw,dr,pl,dl,dr,bs,vw,bs,bs,bs,bs,bs,bs,vw,bs,dl,dr,pl,dl,hw,hw,hw,hw,hw},
        {bs,bs,bs,bs,bs,bs,pl,bs,bs,bs,vw,bs,bs,bs,bs,bs,bs,vw,bs,bs,bs,pl,bs,bs,bs,bs,bs,bs},
        {hw,hw,hw,hw,hw,dl,pl,dr,dl,bs,vw,bs,bs,bs,bs,bs,bs,vw,bs,dr,dl,pl,dr,hw,hw,hw,hw,hw},
        {bs,bs,bs,bs,bs,vw,pl,vw,vw,bs,dl,hw,hw,hw,hw,hw,hw,dr,bs,vw,vw,pl,vw,bs,bs,bs,bs,bs},
        {bs,bs,bs,bs,bs,vw,pl,vw,vw,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,vw,vw,pl,vw,bs,bs,bs,bs,bs},
        {bs,bs,bs,bs,bs,vw,pl,vw,vw,bs,dr,hw,hw,hw,hw,hw,hw,dl,bs,vw,vw,pl,vw,bs,bs,bs,bs,bs},
        {dr,hw,hw,hw,hw,dr,pl,dl,dr,bs,dl,hw,hw,id,id,hw,hw,dr,bs,dl,dr,pl,dl,hw,hw,hw,hw,dl},
        {vw,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,vw,vw,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,vw},
        {vw,pl,dr,hw,hw,dl,pl,dr,hw,hw,hw,dl,pl,vw,vw,pl,dr,hw,hw,hw,dl,pl,dr,hw,hw,dl,pl,vw},
        {vw,pl,dl,hw,id,vw,pl,dl,hw,hw,hw,dr,pl,dl,dr,pl,dl,hw,hw,hw,dr,pl,vw,id,hw,dr,pl,vw},
        {vw,pp,pl,pl,vw,vw,pl,pl,pl,pl,pl,pl,pl,bs,bs,pl,pl,pl,pl,pl,pl,pl,vw,vw,pl,pl,pp,vw}, //[25][13] - pacman spawn
        {id,hw,dl,pl,vw,vw,pl,dr,dl,pl,dr,hw,hw,hw,hw,hw,hw,dl,pl,dr,dl,pl,vw,vw,pl,dr,hw,id},
        {id,hw,dr,pl,dl,dr,pl,vw,vw,pl,dl,hw,hw,id,id,hw,hw,dr,pl,vw,vw,pl,dl,dr,pl,dl,hw,id},
        {vw,pl,pl,pl,pl,pl,pl,vw,vw,pl,pl,pl,pl,vw,vw,pl,pl,pl,pl,vw,vw,pl,pl,pl,pl,pl,pl,vw},
        {vw,pl,dr,hw,hw,hw,hw,id,id,hw,hw,dl,pl,vw,vw,pl,dr,hw,hw,id,id,hw,hw,hw,hw,dl,pl,vw},
        {vw,pl,dl,hw,hw,hw,hw,hw,hw,hw,hw,dr,pl,dl,dr,pl,dl,hw,hw,hw,hw,hw,hw,hw,hw,dr,pl,vw},
        {vw,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,pl,vw},
        {dl,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,hw,dr},
        {bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs},
        {bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs},
        {bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs,bs},
    };

    ::screen = screen;
}

int countPellets(){
    int cont = 0;
    for(long unsigned int row = 0; row < screen.size(); row++){
        for(long unsigned int col = 0; col < screen[0].size(); col++){
            if(screen[row][col] == PELLET) cont++;
        }
    }
    return cont;
}