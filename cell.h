#ifndef CELL_H
#define CELL_H
#include "observer.h"
#include "subject.h"
#include <string>

class Info;
class State;
class Player;


class Cell: public Subject<Info, State>, public Observer<Info, State> {
    std::string name;
    int posn;
    Info info;
public:
    Cell(std::string name);
    virtual void notify(Subject<Info, State> *whoFrom) = 0;
    void notifyObservers();
    std::string getName() const;
};



#endif