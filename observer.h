#ifndef OBSERVER_H
#define OBSERVER_H
#include <memory>

template <typename StateType>
class Subject;

template <typename StateType>
class Observer {
    public:
        virtual void notify(std::shared_ptr<Subject<StateType>> whoFrom) = 0;
};

#endif
