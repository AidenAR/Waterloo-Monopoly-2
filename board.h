#ifndef BOARD_H
#define BOARD_H
#include <vector>

class TextDisplay;
class Player;
class Cell;

class Board {
    std::vector<Player> playerList;
    TextDisplay *td = nullptr; // The text display.
    std::vector<Cell> cellList; // The list of cells on the board


 public:
    ~Board();

    void init();
    int rollDice();
    Player *currentPlayer();
    void loadGame();
    void saveGame();
};

#endif