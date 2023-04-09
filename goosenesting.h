#ifndef GOOSENESTING_H
#define GOOSENESTING_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class Goose: public NonOwnable {
    public:
        Goose(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price);
};

#endif