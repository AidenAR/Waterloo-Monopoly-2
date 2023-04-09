#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>

template <typename StateType> class Subject;
class Cell;
class Board;

class TextDisplay: public Observer<State> {
    std::vector<std::vector<char>> theDisplay;
    Board &board;
    void TextDisplay::updatePlayerPosn(shared_ptr<Cell> cell);
    void TextDisplay::updateImprovement(shared_ptr<Cell> cell);
    public:
        TextDisplay(Board &board);
        void TextDisplay::notify(std::shared_ptr<Subject<State>> whoFrom);
        friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif