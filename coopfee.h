#ifndef COOPFEE_H
#define COOPFEE_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class CoopFee: public NonOwnable {
    public:
        void notify(Subject<Info, State> &whoNotified) override;
};

#endif