#include "subject.h"
#include "observer.h"
#include <iostream>
#include "state.h"
#include <memory>
#include <vector>
using namespace std;

template <typename StateType>
void Subject<StateType>::attach(shared_ptr<Observer<StateType>> o) {
    observers.emplace_back(o);
}

template <typename StateType>
void Subject<StateType>::detach(shared_ptr<Observer<State>> o) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == o) {
            observers.erase(it);
            break;
        } 
    }
}

template <typename StateType>
void Subject<StateType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

template <typename StateType>
StateType Subject<StateType>::getState() const {
    return StateType();
}

template <typename StateType>
void Subject<StateType>::setState(StateType state) {}