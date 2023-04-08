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

    // Subject.cc for now will implement dummy methods that dont do anything useful.

    virtual InfoType *getInfo() const;
    virtual void setInfo(InfoType info);
    virtual StateType *getState() const;
    virtual void setState(StateType state);

    void attach(std::shared_ptr<Object<Info, State> *> o);
    void detach(std::shared_ptr<Object<Info, State> *> o);
    void notifyObservers();
};

#endif
