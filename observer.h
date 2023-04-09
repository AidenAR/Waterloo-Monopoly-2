#ifndef OBSERVER_H
#define OBSERVER_H

template <typename StateType>
class Subject;

template <typename StateType>
class Observer {
    virtual void notify(std::shared_ptr<Subject<State>> whoFrom) = 0;
};

#endif
