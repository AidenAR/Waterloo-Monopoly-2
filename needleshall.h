#ifndef NEEDLESHALL_H
#define NEEDLESHALL_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class NeedlesHall: public NonOwnable {
    public:
        void notify(Subject<Info, State> &whoNotified) override;
};

#endif