#ifndef STATE_H
#define STATE_H

enum class StateType{Purchase, Mortgage, Trade, Unmortgage, Bankrupt, Move};

class State{
    StateType type;
    int playerPosn;
};

#endif