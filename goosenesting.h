#ifndef GOOSENESTING_H
#define GOOSENESTING_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class Goose: public NonOwnable {
    public:
        void notify(Subject<Info, State> &whoNotified) override;
};

#endif