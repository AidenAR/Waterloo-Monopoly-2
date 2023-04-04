#ifndef SUBJECT_H
#define SUBJECT_H

template <typename InfoType, typename StateType> class Observer;

template <typename InfoType, typename StateType> class Subject {
    protected:
    void setState(StateType newS);
    public:
    void attach(Observer<InfoType, StateType> *o);
    void detach(Observer<InfoType, StateType> *o);
    virtual InfoType getInfo() = 0;
};

#endif
