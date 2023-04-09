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
    bool isMortgage = false;
public:
    Ownable(Board &board, std::string name, int posn, int i, int j);

    virtual int improvementCost() = 0;
    virtual void sellImprovement() = 0;
    virtual void buyImprovement() = 0;
    virtual void payTuition(Player *p) = 0;
    virtual void mortgage() = 0;
    virtual void unMortgage() = 0;
    virtual void notify(std::shared_ptr<Subject<Info, State>> whoFrom) = 0;
    void auction();
    void setOwner(Player *p);
};

#endif //OWNABLE_H
