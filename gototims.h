#ifndef GOTOTIMS_H
#define GOTOTIMS_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class GoToTims: public NonOwnable {
    public:
        void notify(Subject<Info, State> &whoNotified) override;
};

#endif