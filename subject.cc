#include "subject.h"

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attach(Observer<InfoType, StateType> *o) {
    observers.emplace_back(o);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::detach(Observer<InfoType, StateType> *o) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == o) {
            observers.erase(it);
            break;
        } 
    }
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

// Workaround for the Info vs State issue

template <typename InfoType, typename StateType>
InfoType Subject<InfoType, StateType>::getInfo() const {
    return InfoType();
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::setInfo(InfoType info) {}

template <typename InfoType, typename StateType>
StateType Subject<InfoType, StateType>::getState() const {
    return StateType();
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::setState(StateType state) {}