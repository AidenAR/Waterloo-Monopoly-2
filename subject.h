#ifndef SUBJECT_H
#define SUBJECT_H

template <typename StateType> class Observer;

template <typename StateType> class Subject {
    std::shared_ptr<std::vector<Observer<StateType>>> observers;

public:
    // Idt its a good idea to require Subjects to have an
    // Info or State attribute, that should be handled by
    // Player and Cell respectively.

    // We need both State and Info accessor methods here, 
    // as the notify methods for Cell and Player take in 
    // a Subject and need some way to access Info and State.

    // Subject.cc for now will implement dummy methods that dont do anything useful.


    virtual StateType *getState();
    virtual void setState(StateType state);

    void attach(std::shared_ptr<Observer<StateType>> o);
    void detach(std::shared_ptr<Observer<StateType>> o);
    void notifyObservers();
};

#endif
