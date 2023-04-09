#ifndef GOTOTIMS_H
#define GOTOTIMS_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class GoToTims: public NonOwnable {
    public:
        GoToTims(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price);
};

#endif