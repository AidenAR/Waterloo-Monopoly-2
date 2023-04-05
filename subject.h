#ifndef SUBJECT_H
#define SUBJECT_H

template <typename InfoType, typename StateType> class Observer;

template <typename InfoType, typename StateType> class Subject {
    // notes:
    // getState() and setState() are not included here as we only want Player class to work with state object
    // similarly, we only want Cell class to work with Info object so no getInfo() or setInfo()

    std::vector<Observer<InfoType, StateType>*> observers;
    public:
    void attach(Observer<InfoType, StateType> *o);
    void detach(Observer<InfoType, StateType> *o);
    void notifyObservers();
};

#endif
