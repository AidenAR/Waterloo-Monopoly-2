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
#include "AcademicBuildings.h"

class Player : public Subject<Info, State> , public Observer<Info, State>{
    char pieceName;
    const int startingMoney = 1500;
    std::string playerName;
    int money;
    int playerPosn;
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
    bool isBankrupt = false;
    std::vector<int> jailRolls;
    State state = State();

    // When we call notifyObservers() but need the respective cell which responded, we store it here.
    // Generally, should be used to add to list of ownedProprties and look at its Info object for making desicions.
    std::shared_ptr<Cell> responseCell = nullptr;
public:
    Player(std::string playerName, char pieceName,
           int money, int rollRims, int playerPosn);

    char getPieceName();
    std::string getPlayerName();
    int getMoney();
    int getPlayerPosn();
    State *getState() const override;
    void setState(State state) override;
    int getRollRims();
    bool getTimsJail();
    int getNumGyms();
    int getNumResidences();
    std::vector<std::shared_ptr<Cell>> getOwnedProperties();
    void addRollRims();
    void subtractRollRims();

    // Movement related
    void moveForward(bool landed = false);
    void placePlayerHere(int newPosn, bool notifyCell);

    // Core player functions
    void attemptBuyProperty(std::shared_ptr<Cell> whoFrom);
    void sellPropertyTo(std::shared_ptr<Player> newOwner, std::string cellName, int salePrice);
    void attemptTrade(std::shared_ptr<Player> tradeTo, std::string give, std::string recieve);
    
    void addFunds(int num);
    void subFunds(int num);
    void printAssets();
    bool getIsBankrupt();
    void setIsBankrupt();
    int playerAssetsWorth(); // Deals with bankrupt
    int getJailTurns();
    void TimsJailTurns(); // Handles jail rolls as well as jail turn

    void notify(std::shared_ptr<Subject<Info, State>> whoFrom) override;
};

#endif //PLAYER_H
