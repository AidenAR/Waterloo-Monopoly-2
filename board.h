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

    std::vector<std::string> pieceList = {"Goose", "GRT Bus", "Tim Hortons Donut", "Professor", "Student", "Money", "Laptop", "Pink Tie"};

    std::vector<std::shared_ptr<Player>> playerList;
    //TextDisplay *td = nullptr; // The text display.
    std::shared_ptr<TextDisplay> td; // The text display
    std::vector<std::shared_ptr<Cell>> Cells; // The list of cells on the board

    char pieceSymbol(std::string pieceName);
    bool findinVector(std::vector<std::string> v, std::string s);
    int totalCups = 0;

 public:

    
    std::vector<std::shared_ptr<Player>> getPlayerList();
    Cell * getCell(int i);
    void addToTotalCups();
    void removeFromTotalCups();
    int getTotalCups();
    std::vector<std::shared_ptr<Cell>> getCellList();

    void initializeCells();
    void init();
    std::vector<int> rollDice();
    void loadGame(std::string f);
    void saveGame(std::string f);
    std::string getWinner();
    bool isGameOver();
    //void auction(std::string cellName);
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif
