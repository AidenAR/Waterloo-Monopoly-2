#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"

class Subject;
class Cell;
class Board;

class TextDisplay: public Observer {
    std::vector<std::vector<char>> theDisplay;
    Board &board;
    
    public:
        TextDisplay(Board &board);
        void updatePlayerPosn(std::shared_ptr<Cell> cell);
        void updateImprovement(std::shared_ptr<Cell> cell);
        void notify(Subject &whoFrom);
        friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif