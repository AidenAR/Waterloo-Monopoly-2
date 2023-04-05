#ifndef INFO_H
#define INFO_H

#include <string>
#include "player.h"

class Reply;

// Only non-ownable properties will use this object; ownable should use OInfo.
struct Info {
    std::string cellName;
};

// Only ownable properties will use this object; non-ownable should use OInfo.
struct OInfo : public Info {
    Player *ownedBy;
    int improveCount;
    int price;
};

#endif
