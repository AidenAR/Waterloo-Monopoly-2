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
    std::unordered_map<std::string, std::pair<int, bool>> FacultyMap =
            {{"Arts1", {0, false}}, {"Arts2", {0, false}}, {"Eng", {0, false}},
             {"Health", {0, false}}, {"Env", {0, false}}, {"Sci1", {0, false}},
             {"Sci2", {0, false}}, {"Math", {0, false}}};
    int numGyms;
    int numResidences;
    bool timsJail;
    int rollRims;
    int jailTurns;
    bool isBankrupt = false;
    std::vector<int> jailRolls;
    State state = State();
    Board *board;


    // When we call notifyObservers() but need the respective cell which responded, we store it here.
    // Generally, should be used to add to list of ownedProprties and look at its Info object for making desicions.
    std::shared_ptr<Cell> responseCell = nullptr;
public:
    Player(Board *board, std::string playerName, char pieceName,
           int money, int rollRims, int playerPosn);

    const int NumArts1 = 2;
    const int NumArts3 = 3;
    const int NumEng = 3;
    const int NumHealth = 3;
    const int NumEnv = 3;
    const int NumSci1 = 3;
    const int NumSci2 = 3;
    const int NumMath = 2;

    char getPieceName();
    std::string getPlayerName();
    int getMoney();
    int getPlayerPosn();
    State *getState() override;
    void setState(State state) override;

    // Tims jail related
    int getRollRims();
    bool getTimsJail();
    void freePlayerFromTimsJail();
    int getJailTurns();
    void TimsJailTurns(); // Handles jail rolls as well as jail turn

    int getNumGyms();
    int getNumResidences();
    std::vector<std::shared_ptr<Cell>> getOwnedProperties();
    void addRollRims();
    void subtractRollRims();
    void setTimsJail(bool j);

    // Movement related
    void moveForward(bool landed = false);
    void placePlayerHere(int newPosn, bool notifyCell);

    // Core player functions
    void attemptBuyProperty(std::shared_ptr<Cell> whoFrom);
    void sellPropertyTo(Player *newOwner, std::string cellName, int salePrice);
    void attemptTrade(Player *tradeTo, std::string give, std::string recieve);
    
    // Ownable property actions
    void attemptAddImprovement(std::string cellName);
    void attemptSellImprovement(std::string cellName);
    void attemptMortgage(std::string cellname);
    void attemptUnmortgage(std::string cellname);
    
    void addFunds(int num);
    void subFunds(int num);
    void printAssets();
    bool getIsBankrupt();
    void setIsBankrupt();
    int playerAssetsWorth(); //Deals with bankrupt
    void partMonopoly();
    
    void addProperty(std::shared_ptr<Ownable> c);
    void setJailTurns(int j);
    void TimsJailCell(Player& p);

    void notify(std::shared_ptr<Subject<Info, State>> whoFrom);
};

#endif //PLAYER_H
