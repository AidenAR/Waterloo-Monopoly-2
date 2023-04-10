#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <memory>
class Subject;

class Observer {
  public:
    virtual void notify(std::shared_ptr<Subject> whoNotified ) = 0;
};

#endif