#ifndef NEEDLESHALL_H
#define NEEDLESHALL_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class NeedlesHall: public NonOwnable {
    public:
        NeedlesHall(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price);
};

#endif