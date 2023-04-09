#ifndef COOPFEE_H
#define COOPFEE_H
#include "nonownable.h"

template <typename StateType> class Subject;

class CoopFee: public NonOwnable {
    public:
        CoopFee(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price);
};

#endif