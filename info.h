#ifndef INFO_H
#define INFO_H

#include <string>
class Reply;
class Player;

// Only non-ownable properties will use this object; ownable should use OInfo.
struct Info {
    string cellName;
    Reply replyObj;
};

// Only ownable properties will use this object; non-ownable should use OInfo.
struct OInfo : public Info {
    Player ownedBy;
    int improveCount;
    int price;
};

struct Reply {
    // Denotes how much money is demanded from the player
    // eg, money=10 implies player has to pay 10, 
    // or like when we cross go the go cell replies by setting money=-200
    int money = 0;
    // Denotes how many spaces on the board player must move
    // eg, moveSpaces=2 means player must move 2 spots forward
    int moveSpaces = 0;
};

#endif
