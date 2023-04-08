#ifndef STATE_H
#define STATE_H

// When it is players turn, we can call one of the methods in Player class (which aiden implementing), 
// which will create a State object to characterize what kind of action player takes.

// Purchase:
// Player initially lands on Cell, Cell responds with its Info object. Player can retrieve cell price and isOwned from that Info.
// If player has enough money and decides to buy it, then send Purchase request. 

// Mortgage/Unmortgage:
// Player specifies cellName that they want to be mortgaged/unmortgaged, and send Mortgage/Unmortgage notification.
// Cell responds saying whether mortgage/unmortgage was succesful or unsuccessful. If successful, run:
// void Player::mortgage(string proertyName) or void Player::unmortgage(string proertyName)
// which changes player values that store properties and players money

// Trade:
// Player specifies cellName they want to trade, and sets newOwner to Player who its being transferred to. 
// Then, set StateType to SellTo. 
// Cell responds with whether successful trade or not. if successful, update both Players by calling:
// void Player::successfulTrade(string proertyName)
// which handles player-side changes

// Bankrupt:
// Call this function only when player net worth < amount owed.
// Player can then decide whether to raise money or declare bankrupcy.
// In case of declaring bankrupty:
//      Foreach property owned by player:
//          set StateType to SellTo, and cellName to that property's name. 
//          If the player owes other player money, then set newOwner* to person who is owed, else set it to nullptr.
//          Send this notification to that property. 
// In case of raise money:
//      Player will specify cellName which they wanna raise.
//      Player can either sell improvements or mortgage. 
//      If sell improvement:
//          set Stateype to SellImprovement. Cell recieving this will remove its improvment and repond w how much money player earns.
//      if mortgage: call mortgage as usual.

// Move:
// Say a player rolls dice and has to move 4 spots. Essentially, player will move forward 1 spot 3 times. 
// However, the fact player is moving means they dont have to collect rent when they just moving across cells. 
// Thus, ownable cells dont do anything. Non-ownable however do sometimes react, ie, for collect-OSAP.
// Just set playerPosn to new player posn, and StateType to Move. The cell which corrosponds to that posn will automatically respond back.
// However, if we have to move 4 spots, the first  times we will send a "Move" notification, however, the 4th time, we send a "Landed" notification,
// which means that is where the player has "Landed" after rolling. 
// It is at this point Ownable cells will respond with stuff like tuition or wtvr.

enum class StateType{Purchase, Mortgage, Unmortgage, SellTo, SellImprovement, Landed, Move, Playing};

struct State {
    StateType type = StateType::Playing;
    int playerPosn = 0;
    std::string cellName = "";
    Player *newOwner = nullptr;
};

#endif
