#ifndef SLC_H
#define SLC_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class Slc: public NonOwnable {
    public:
        Slc(Board &board, std::string name, int pos, int i, int j);
};

#endif