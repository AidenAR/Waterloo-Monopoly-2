#ifndef OBSERVER_H
#define OBSERVER_H

template <typename InfoType, typename StateType> class Subject;

template <typename InfoType, typename StateType> class Observer {
    virtual void notify(std::shared_ptr<Subject<Info, State>> whoFrom) = 0;
};

#endif
