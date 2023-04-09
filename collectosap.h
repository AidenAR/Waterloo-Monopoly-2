#ifndef COLLECTOSAP_H
#define COLLECTOSAP_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class CollectOsap: public NonOwnable {
    public:
        CollectOsap::CollectOsap(Board &board, std::string name, int pos, int i, int j);
};

#endif