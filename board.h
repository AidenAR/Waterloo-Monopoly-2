#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <memory>

class TextDisplay;
class Player;
class Cell;

class Board {

    const int OsapCell = 0;
    const int TimsCell = 10;
    const int goToTimsCell = 30;
    const int maxPlayers = 8;
    const int numCells = 40;

    std::vector<Player> playerList;
    //TextDisplay *td = nullptr; // The text display.
    std::shared_ptr<TextDisplay> td; // The text display
    std::vector<Cell> cellList; // The list of cells on the board


 public:
    ~Board();

    void init();
    int rollDice();
    Player *currentPlayer();
    void loadGame(std::string f);
    void saveGame(std::string f);
};

#endif