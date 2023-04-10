#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "observer.h"
class Observer;

class Subject: public std::enable_shared_from_this <Subject>{
    std::vector<Observer *> observers;

  public:
    void attach(Observer *o);  
    void notifyObservers();
    virtual std::string getName()=0;

};

#endif


// #ifndef SUBJECT_H
// #define SUBJECT_H
// #include <vector>
// #include <memory>
// #include "state.h"
// #include "observer.h"

// // /* A note on InfoType and StateType:

// //    We have separated the collection of fields into two parts:  its Info
// //    and its State.

// //    Info is for the parts of the subjject inherent to what it is:  its position
// //    and its colour.

// //    State is for the parts of the subject that, when changed, trigger
// //    notifications.  This is the information that the Observer "gets" when it
// //    calls getState on the subject.  It comprises the type of state, a direction,
// //    and a colour.  For more details, see state.h.
// // */

// // // DO NOT MODIFY THIS FILE!

// // template <typename StateType> class Observer;

// // template <typename StateType> class Subject {
// //   std::vector<Observer<StateType>*> observers;
// //   StateType state;
// //  protected:
// //   virtual void setState(StateType newS);
// //  public:
// //   void attach(Observer<StateType> *o);  
// //   void notifyObservers();
// //   virtual StateType *getState();
// // };

// // template <typename StateType>
// // void Subject<StateType>::attach(Observer<StateType> *o) {
// //   observers.emplace_back(o);
// // }

// // template <typename StateType>
// // void Subject<StateType>::notifyObservers() {
// //   for (auto &ob : observers) ob->notify(*this);
// // }

// // template <typename StateType>
// // void Subject<StateType>::setState(StateType newS) { state = newS; }

// // template <typename StateType>
// // StateType *Subject<StateType>::getState() {
// //     return nullptr;
// // }
// // #endif


// // #ifndef SUBJECT_H
// // #define SUBJECT_H


// class Subject { //}: public std::enable_shared_from_this <Subject<StateType>> {
//     std::vector<Observer *> observers;

// public:
//     // Idt its a good idea to require Subjects to have an
//     // Info or State attribute, that should be handled by
//     // Player and Cell respectively.

//     // We need both State and Info accessor methods here, 
//     // as the notify methods for Cell and Player take in 
//     // a Subject and need some way to access Info and State.

//     // Subject.cc for now will implement dummy methods that dont do anything useful.


//     virtual State *getState();
//     virtual void setState(State state);

//     void attach(Observer *);
//     // void detach(std::shared_ptr<Observer<State>> o);
//     void notifyObservers();
// };

// void Subject::attach(Observer *o) {
//     observers.emplace_back(o);
// }


// void Subject::notifyObservers() {
//   for (auto &ob : observers) {
//         ob->notify(*this);
//     }
// }


// State *Subject::getState() {
//     return nullptr;
// }

// void Subject::setState(State state) {}

// #endif
