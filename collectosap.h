#ifndef COLLECTOSAP_H
#define COLLECTOSAP_H
#include "nonownable.h"

template <typename StateType> class Subject;

class CollectOsap: public NonOwnable {
    public:
        CollectOsap::CollectOsap(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price);
};

#endif