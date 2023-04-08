#ifndef GOTOTIMS_H
#define GOTOTIMS_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class GoToTims: public NonOwnable {
    public:
        GoToTims(Board &board, std::string name, int pos, int i, int j);
};

#endif