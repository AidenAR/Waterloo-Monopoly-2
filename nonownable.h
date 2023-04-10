#ifndef NONOWNABLE_H
#define NONOWNABLE_H
#include "cell.h"

class Subject;
class State;

class NonOwnable: public Cell {
    public:
        NonOwnable(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price);
        void notify(Subject &whoFrom);
};

#endif