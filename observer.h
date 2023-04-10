#ifndef OBSERVER_H
#define OBSERVER_H
#include <memory>

class Subject;

class Observer {
    public:
        virtual void notify(std::shared_ptr<Subject> whoFrom) = 0;
};

#endif
