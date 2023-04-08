#ifndef TUITION_H
#define TUITION_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class Tuition: public NonOwnable {
    public:
        Tuition(Board &board, std::string name, int pos, int i, int j);
};

#endif