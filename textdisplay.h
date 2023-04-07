#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>

template <typename InfoType, typename StateType> class Subject;
class Cell;
class Info;
class Board;

class TextDisplay: public Observer<Info, State> {
    std::vector<std::vector<char>> theDisplay;
    void updateDisplay(shared_ptr<Cell> cell, int r, int c);
    public:
        TextDisplay();
        void notify(Subject<Info, State> &whoNotified) override;
        friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif