//
// Created by aiden on 03/04/2023.
//

#ifndef RESIDENCES_H
#define RESIDENCES_H

#include "ownable.h"
#include <unordered_map>
#include "player.h"
#include "state.h"
#include "observer.h"
#include "subject.h"
//Note: Num Resi owned is in player
//Also this has acess to info since it inherits from Ownable

class Residences: public Ownable {
    //int res_cost = $200; [from Info]
public:
    const int oneResRent = 25;
    const int twoResRent = 50;
    const int threeResRent = 100;
    const int fourResRent = 200;
    const int resCost = 200;
    Residences(Board &board, std::string name, int pos, int i, int j, bool ownable, OwnableType otype, int price);
    ~Residences();
    void payTuition(Player *p); //payRent is like payTuition
    void mortgage();
    void unMortgage();
    void notify(std::shared_ptr<Subject<State>> whoFrom);
};


#endif //RESIDENCES_H
