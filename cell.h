#ifndef CELL_H
#define CELL_H
#include "observer.h"
#include "subject.h"
#include <string>

class Info;
class State;
class Player;
class Board;


class Cell: public Subject<Info, State>, public Observer<Info, State> {
    std::string name;
    int posn;
    int i;
    int j;
    Board &board;
    Info info;
    public:
        Cell(Board &board, std::string name, int posn, int i, int j);
        virtual void notify(Subject<Info, State> &whoNotified) = 0;
        //virtual Info getInfo() const;
        void notifyObservers();
};



#endif