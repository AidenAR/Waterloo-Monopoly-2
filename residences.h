//
// Created by aiden on 03/04/2023.
//

#ifndef RESIDENCES_H
#define RESIDENCES_H

#include "ownable.h"
#include <unordered_map>
#include "info.h"
#include "player.h"
#include "state.h"
#include "info.h"
#include "observer.h"
#include "subject.h"
//Note: Num Resi owned is in player
//Also this has acess to info since it inherits from Ownable

class Residences: public Ownable{
private:
    Board &board;
    std::string name;
    int pos;
    int i;
    int j;
    //int res_cost = $200; [from Info]
public:
    const int oneResRent = 25;
    const int twoResRent = 50;
    const int threeResRent = 100;
    const int fourResRent = 200;
    const int resCost = 200;
    Residences(board &b, std::string name, int pos, int i, int j);
    Residences~();
    void payTuition(Player *p) override; //payRent is like payTuition
    void mortgage(std::string cellName) override;
    void unMortgage(std::string cellName) override;
    void notify(Subject<Info, State> &whoNotified) override;
};


#endif //RESIDENCES_H
