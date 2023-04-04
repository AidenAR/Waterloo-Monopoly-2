#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>

template <typename InfoType, typename StateType> class Subject;

template <typename InfoType, typename StateType> class TextDisplay: public Observer<Info, State> {
    public:
        TextDisplay();
        void notify(Subject<Info, State> &whoNotified) override;
        friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif