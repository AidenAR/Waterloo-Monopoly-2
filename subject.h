#ifndef SUBJECT_H
#define SUBJECT_H

template <typename InfoType, typename StateType> class Observer;

template <typename InfoType, typename StateType> class Subject {
    std::vector<Observer<InfoType, StateType> *> observers;

public:
    // Idt its a good idea to require Subjects to have an
    // Info or State attribute, that should be handled by
    // Player and Cell respectively.

    // We need both State and Info accessor methods here, 
    // as the notify methods for Cell and Player take in 
    // a Subject and need some way to access Info and State.

    virtual InfoType getInfo() const = 0;
    virtual void setInfo(InfoType info) = 0;
    virtual StateType getState() const = 0;
    virtual void setState(StateType state) = 0;

    void attach(Observer<InfoType, StateType> *o);
    void detach(Observer<InfoType, StateType> *o);
    void notifyObservers();
};

#endif
