#ifndef TUITION_H
#define TUITION_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class Tuition: public NonOwnable {
    public:
        void notify(Subject<Info, State> &whoNotified) override;
};

#endif