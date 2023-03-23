// Your First C++ Program
#include <iostream>
#include <string>
#include <vector>
#include <string>
#include "game.h"

using namespace std;

// this is here to remove warnings, later maybe i'll use args
int main(/*int argc, char *argv[]*/)
{

    Screen gameScreen;
    gameScreen.setupGameField();
    Game game(gameScreen);

    game.play();

    return 0;
}
