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
    const char space = ' ';
    
    public:
        TextDisplay(Board &board);
        void updatePlayerPosn(Cell *cell);
        void updateImprovement(Cell *cell);
        void notify(Subject *whoFrom) override;
        friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif