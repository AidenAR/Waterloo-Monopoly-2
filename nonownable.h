#ifndef NONOWNABLE_H
#define NONOWNABLE_H
#include "cell.h"

template <typename InfoType, typename StateType> class Subject;
class Info;
class State;

class NonOwnable: public Cell {
    public:
        NonOwnable(Board &board, std::string name, int posn, int i, int j);
        Info getInfo() const;
};

#endif