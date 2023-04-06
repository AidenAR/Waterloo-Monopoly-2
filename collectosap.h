#ifndef COLLECTOSAP_H
#define COLLECTOSAP_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class CollectOsap: public NonOwnable {
    public:
        CollectOsap::CollectOsap(std::string name, int index);
        void notify(Subject<Info, State> &whoNotified) override;
};

#endif