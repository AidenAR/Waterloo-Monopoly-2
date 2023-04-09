#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

/* A note on InfoType and StateType:

   We have separated the collection of fields into two parts:  its Info
   and its State.

   Info is for the parts of the subjject inherent to what it is:  its position
   and its colour.

   State is for the parts of the subject that, when changed, trigger
   notifications.  This is the information that the Observer "gets" when it
   calls getState on the subject.  It comprises the type of state, a direction,
   and a colour.  For more details, see state.h.
*/

// DO NOT MODIFY THIS FILE!

template <typename StateType> class Observer;

template <typename StateType> class Subject {
  std::vector<Observer<StateType>*> observers;
  StateType state;
 protected:
  virtual void setState(StateType newS);
 public:
  void attach(Observer<StateType> *o);  
  void notifyObservers();
  virtual StateType *getState();
};

template <typename StateType>
void Subject<StateType>::attach(Observer<StateType> *o) {
  observers.emplace_back(o);
}

template <typename StateType>
void Subject<StateType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

template <typename StateType>
void Subject<StateType>::setState(StateType newS) { state = newS; }

template <typename StateType>
StateType *Subject<StateType>::getState() {
    return StateType();
}
#endif


// #ifndef SUBJECT_H
// #define SUBJECT_H

// template <typename StateType> class Observer;

// template <typename StateType> class Subject {
//     std::vector<Observer<StateType>*> observers;

// public:
//     // Idt its a good idea to require Subjects to have an
//     // Info or State attribute, that should be handled by
//     // Player and Cell respectively.

//     // We need both State and Info accessor methods here, 
//     // as the notify methods for Cell and Player take in 
//     // a Subject and need some way to access Info and State.

//     // Subject.cc for now will implement dummy methods that dont do anything useful.


//     virtual StateType *getState();
//     virtual void setState(StateType state);

//     void attach(Observer<StateType> o);
//     // void detach(std::shared_ptr<Observer<StateType>> o);
//     void notifyObservers();
// };
// template <typename StateType>
// void Subject<StateType>::attach(shared_ptr<Observer<StateType>> o) {
//     observers.emplace_back(o);
// }

// // template <typename StateType>
// // void Subject<StateType>::detach(shared_ptr<Observer<StateType>> o) {
// //     for (auto it = observers.begin(); it != observers.end(); ++it) {
// //         if (*it == o) {
// //             observers.erase(it);
// //             break;
// //         } 
// //     }
// // }

// template <typename StateType>
// void Subject<StateType>::notifyObservers() {
//   for (auto &ob : observers) ob->notify(*this);
// }

// template <typename StateType>
// StateType *Subject<StateType>::getState() {
//     return StateType();
// }

// template <typename StateType>
// void Subject<StateType>::setState(StateType state) {}

// #endif
