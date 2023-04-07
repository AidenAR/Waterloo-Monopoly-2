#ifndef INFO_H
#define INFO_H

#include <string>
#include "player.h"

enum OwnableType{Academic, Residence, Gym};

struct Info {
    // This is s general property. Use case is whenever player sends some notification to cell or tells it to do something, if task was successful we convey it through here. 
    // eg, for Mortgage/Unmortgage,Trade,etc
    bool wasSuccesful;

    bool ownable;
    std::string cellName;
    int posn;

    // Only ownable properties will use the following attributes; non-ownable should use just cellName and posn, and the Player obj decides what to do from there.
    OwnableType otype;
    Player *ownedBy;
    int improveCount;
    int price;
    bool isMortgaged = false;
};

#endif
