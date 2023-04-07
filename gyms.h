//
// Created by aiden on 04/04/2023.
//

#ifndef GYMS_H
#define GYMS_H

#include "ownable.h"
#include "info.h"
#include "player.h"


//Note: Num Gyms owned is in player
//Also this has acsess to info since it inherits from Ownable


class Gyms : public Ownable {
    //int gym_cost = $150; [from Info]
public:
    void payTuition() override;  //payMembership is like payTuition
    void mortgage() override;
    void unMortgage() override;
    void notify(Subject<Info, State> &whoNotified) override;
    // void auction();????
};

#endif //GYMS_H
