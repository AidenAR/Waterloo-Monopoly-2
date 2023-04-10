#ifndef OBSERVER_H
#define OBSERVER_H
#include <memory>

class Subject;

class Observer {
    public:
        virtual void notify(Subject &whoFrom) = 0;
};

#endif
