#ifndef SLC_H
#define SLC_H
#include "nonownable.h"

template <typename StateType> class Subject;

class Slc: public NonOwnable {
    public:
        Slc(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price);
};

#endif