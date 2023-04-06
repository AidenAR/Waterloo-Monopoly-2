//
// Created by aiden on 03/04/2023.
//

#ifndef OWNABLE_H
#define OWNABLE_H
#include "cell.h"
#include "player.h"
template <typename InfoType, typename StateType> class Subject;
class Info;
class State;

class Ownable: public Cell {
protected:
    Info info;
    bool isMortgage = false;
public:
    virtual int improvementCost() = 0;
    virtual void sellImprovement() = 0;
    virtual void buyImprovement() = 0;
    virtual void payTuition() = 0;
    virtual void mortgage() = 0;
    virtual void unMortgage() = 0;
    virtual void notify(Subject<Info, State> &whoNotified) = 0;
    Info getInfo() const;
    virtual bool partMonopoly() = 0;
    void auction();
};

#endif //OWNABLE_H