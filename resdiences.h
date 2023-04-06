//
// Created by aiden on 03/04/2023.
//

#ifndef RESIDENCES_H
#define RESIDENCES_H

#include "ownable.h"
#include "info.h"
#include "player.h"

//Note: Num Resi owned is in player
//Also this has acess to info since it inherits from Ownable

class Residences: public Ownable{
    //int res_cost = $200; [from Info]
public:
    void payTuition() override;  //payRent is like payTuition
    void mortgage() override;
    void unMortgage() override;
    void notify(Subject<Info, State> &whoNotified) override;
};


#endif //RESIDENCES_H