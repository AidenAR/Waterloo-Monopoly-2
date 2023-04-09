//
// Created by aiden on 04/04/2023.
//

#ifndef GYMS_H
#define GYMS_H

#include "ownable.h"
#include <unordered_map>
#include "info.h"
#include "player.h"
#include "state.h"
#include "info.h"
#include "observer.h"
#include "subject.h"
#include "board.h"

//Note: Num Gyms owned is in player
//Also this has acess to info since it inherits from Ownable


class Gyms : public Ownable {
    //int gym_cost = $150; [from Info]
public:
    const int gym_cost = 150;
    const int oneGym = 4;
    const int twoGym = 10;
    Gyms(Board &b, std::string name, int pos, int i, int j);
    Board getBoard(Gyms& g);
    ~Gyms();
    void payTuition(Player *p) override; //payMembership is like payTuition
    void mortgage() override;
    void unMortgage() override;
    void notify(std::shared_ptr<Subject<Info, State>> whoFrom) override;
    // void auction();????
};

#endif //GYMS_H