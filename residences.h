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
    void payTuition(Player *p) override; //payRent is like payTuition
    void mortgage() override;
    void unMortgage() override;
    void notify(std::shared_ptr<Subject<Info, State>> whoFrom) override;
};


#endif //RESIDENCES_H
