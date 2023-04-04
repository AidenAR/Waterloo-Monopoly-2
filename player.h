//
// Created by aiden on 03/04/2023.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "subject.h"
#include "observer.h"
#include "state.h"
#include "info.h"
#include "board.h"
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>


class Player : public Subject<Info, State> {
    char pieceName;
    std::string playerName;
    int money;
    Cell playerPosn;
    std::vector<std::shared_ptr<Cell>> ownedProperties;
    std::unordered_map<std::string, int> FacultyMap =
            {{"Arts1", 0}, {"Arts2", 0}, {"Eng", 0},
             {"Health", 0}, {"Env", 0}, {"Sci1", 0},
             {"Sci2", 0}, {"Math", 0}};
    int numGyms;
    int numResidences;
    bool timsJail;
    int rollRims;
    int jailTurns;
    std::vector<int> jailRolls;
public:
    char getPieceName();
    std::string playerName();
    int getMoney();
    Cell getPlayerPosn();
    State getState();
    int getRollRims();
    bool getTimsJail;
    int getNumGyms;
    int getNumResidences;
    std::vector<std::shared_ptr<Cell>> getOwnedProperties();
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
#endif //PLAYER_H
