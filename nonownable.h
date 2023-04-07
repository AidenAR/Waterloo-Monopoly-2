#ifndef NONOWNABLE_H
#define NONOWNABLE_H
#include "cell.h"

template <typename InfoType, typename StateType> class Subject;
class Info;
class State;

class NonOwnable: public Cell {
    public:
        virtual void notify(Subject<Info, State> &whoNotified) = 0;
};

#endif