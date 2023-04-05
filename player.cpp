//
// Created by aiden on 03/04/2023.
//

#include "player.h"
using namespace std;
#include <string>

Player::Player(string playerName, char pieceName, int money, int rollRims, Cell playerPosn):
    playerName{playerName}, pieceName{pieceName},
    money{startingMoney}, rollRims{rollRims},
    playerPosn{0}, numGyms{0}, numResidences{0},
    jailTurns{0}, timsJail{false} {
}

char Player::getPieceName() {
    return pieceName;
}


string Player::getPlayerName() {
    return playerName;
}


int Player::getMoney() {
    return money;
}


int Player::getPlayerPosn() {
    return  playerPosn;
}


int Player::getRollRims() {
    return rollRims;
}


State Player::getState() {
    return state;
}


bool Player::getTimsJail {
    return timsJail;
}


int Player::getNumGyms {
    return numGyms;
};


int Player::getNumResidences {
    return numResidences;
};


vector<std::shared_ptr<Cell>> Player::getOwnedProperties {

};

class Player : public Subject<Info, State> {
    char pieceName;
    const int StartingMoney = 1500;
    std::string playerName;
    int money;
    Cell playerPosn;
    std::vector<std::shared_ptr<Cell>> ownedProperties;
    std::unordered_map<std::string, int> FacultyMap =
            {{"Arts1", 0}, {"Arts2", 0}, {"Eng", 0},
             {"Health", 0}, {"Env", 0}, {"Sci1", 0},
             {"Sci2", 0}, {"Math", 0}};

public:


    void addRollRims();
    void subtractRollRims();
    void rollMove(); //set Pos after Dice Roll
    void purchaseProperties(std::shared_ptr<Cell> c);
    void SellProperties(Player *new_owner, std::shared_ptr<Cell> c);
    void BuyProperties(std::shared_ptr<Cell> c);
    void addFunds(int num);
    void subFunds(int num);
    void moveMoney();
    void printAssets();
    int playerAssetsWorth(); //Deals with bankrupt
    int getJailTurns();
    void TimsJailTurns(); //Handles jail rolls as well as jail tur
};