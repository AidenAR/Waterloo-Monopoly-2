#ifndef COLLECTOSAP_H
#define COLLECTOSAP_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class CollectOSAP: public NonOwnable {
    public:
        void notify(Subject<Info, State> &whoNotified) override;
};

#endif