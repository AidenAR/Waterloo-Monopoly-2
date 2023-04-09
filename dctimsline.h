#ifndef DC_TIMS_LINE_H
#define DC_TIMS_LINE_H
#include "nonownable.h"

template <typename StateType> class Subject;

class DCTimsLine: public NonOwnable {
    public:
        DCTimsLine(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price);
};

#endif