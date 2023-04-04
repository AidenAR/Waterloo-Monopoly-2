#ifndef DC_TIMS_LINE_H
#define DC_TIMS_LINE_H
#include "nonownable.h"

template <typename InfoType, typename StateType> class Subject;

class DCTimsLine: public NonOwnable {
    public:
        void notify(Subject<Info, State> &whoNotified) override;
};

#endif