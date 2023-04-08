#ifndef COOPFEE_H
#define COOPFEE_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class CoopFee: public NonOwnable {
    public:
        CoopFee(Board &board, std::string name, int pos, int i, int j);
};

#endif