#ifndef DC_TIMS_LINE_H
#define DC_TIMS_LINE_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class DCTimsLine: public NonOwnable {
    public:
        DCTimsLine(Board &board, std::string name, int pos, int i, int j);
};

#endif