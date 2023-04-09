#ifndef TUITION_H
#define TUITION_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class Tuition: public NonOwnable {
    public:
        Tuition(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price);
};

#endif