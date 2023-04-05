#ifndef STATE_H
#define STATE_H

// When it is players turn, we can call one of the methods in Player class (which aiden implementing), 
// which will create a State object to characterize what kind of 


enum class StateType{PurchaseRequest, PurchaseSuccesful, Mortgage, Trade, Unmortgage, Bankrupt, PrevPosn, Playing};

class State{
    StateType type;
    int playerPosn;
};

#endif
