#ifndef SUBJECT_H
#define SUBJECT_H

class Observer;

template <InfoType, StateType> class Subject {
    protected:
    void setState(StateType newS);
    public:
    void attach(Observer<InfoType, StateType> *o);
    void detach(Observer<InfoType, StateType> *o);
    virtual InfoType getInfo() = 0;
};

#endif
