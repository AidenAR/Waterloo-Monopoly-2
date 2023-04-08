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
    Board &board;
    void TextDisplay::updatePlayerPosn(shared_ptr<Cell> cell);
    void TextDisplay::updateImprovement(shared_ptr<Cell> cell);
    public:
        TextDisplay(Board &board);
        void TextDisplay::notify(Subject<Info, State> &whoNotified) override;
        friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif