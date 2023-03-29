# pacPlus
Pac-Man in C++

The goal of this project is to Implement PACMAN in C++, to later implement an AI for PACMAN

### Building and running (linux)
 - To build on linux, you'll need CMake
 - After installing CMake (if you don't have installed), run these commands on terminal
```
git clone https://github.com/Kovalski-rgb/pacPlus.git
cd pacPlus
./build.sh
```

 - To run, just execute the `PacMan` file inside `build/` folder on your project. 

### TODO list
- [x] Screen Printing in CLI
  - [x] Printing Colors on the CLI version
  - [x] Printing Pellets with different font color than walls
  - [x] Printing Pacman with yellow background for contrast
  - [x] Printing Ghosts
- [ ] Player Movement
  - [x] Up, Down, Left and Right
  - [ ] Instant direction change (right now sometimes it takes >~50ms to turn)
  - [ ] Scroll to other side then crossing the map border
- [ ] Interacting with collectibles
  - [x] Pellets increase player score by 10
  - [x] Power Pellets increase player score by 50
  - [ ] Collecting Power Pellets change ghosts states to frightened
- [ ] Score
  - [ ] Score display on top of the map
- [ ] High Scores
  - [ ] Store HighScores on an external file
  - [ ] Display highscores bellow the actual score
- [ ] Ghosts (with AI)
  - [ ] Interact with PacMan
  - [ ] Blinky 
    - [ ] Complex AI
    - [x] Simple AI (random)
  - [ ] Pinky
    - [ ] Complex AI
    - [x] Simple AI (random)
  - [ ] Inky
    - [ ] Complex AI
    - [x] Simple AI (random)
  - [ ] Clyde
    - [ ] Complex AI
    - [x] Simple AI (random)
- [ ] GUI (maybe this'll be expanded later)
- [ ] Menu before game
  - [ ] Title screen with logo
  - [ ] Sound(maybe?)
  - [ ] Show HighScore on TitleScreen
- [x] Startup CountDown (wait 3s before pacman moves)
- [ ] PacMan AI
  - [ ] Get all pellets as fast as posible
  - [ ] Get the max score in x time

