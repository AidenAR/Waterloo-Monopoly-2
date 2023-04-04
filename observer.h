#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

template <InfoType, StateType> class Observer {
    virtual void notify(Subject<InfoType, StateType> &whoFrom) = 0;
};

#endif
