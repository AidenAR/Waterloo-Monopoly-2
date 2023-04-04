#ifndef SLC_H
#define SLC_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class Slc: public NonOwnable {
    public:
        void notify(Subject<Info, State> &whoNotified) override;
};

#endif