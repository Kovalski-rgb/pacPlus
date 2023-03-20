// Your First C++ Program
#include <iostream>
#include <string>
#include <vector>
#include "gameScreen.h"

using namespace std;

// this is here to remove warnings, later maybe i'll use args
int main(/*int argc, char *argv[]*/)
{
    setupGameVariables();
    setupGameField();

    char separator = ' ';
    string background = BG_BLACK;
    string font = F_BLUE;

    for (long unsigned int row = 0; row < screen.size(); row++){
        for(long unsigned int col = 0; col < screen[0].size(); col++){

            font = F_BLUE;
            if(screen[row][col] == PELLET || screen[row][col] == POWER_PELLET){
                font = F_WHITE;
            }
            
            cout << background << separator << font << (char) screen[row][col] << BG_F_RESET;
        }
        cout << endl;
    }
    cout << background << F_WHITE << countPellets() << BG_F_RESET << endl;
    return 0;
}
