//
// Created by aiden on 03/04/2023.
//

#include "player.h"
#include <string>
#include <algorithm>

using namespace std;
#include <cstdlib>
#include <iostream>


Player::Player(string playerName, char pieceName, int money, int rollRims, Cell playerPosn):
    playerName{playerName}, pieceName{pieceName},
    money{startingMoney}, rollRims{rollRims},
    playerPosn{0}, numGyms{0}, numResidences{0},
    jailTurns{0}, timsJail{false},
    state{StateType::Playing, 0} {
    vector<int> jailRolls{0}
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


bool Player::getTimsJail() {
    return timsJail;
}


int Player::getNumGyms() {
    return numGyms;
}


int Player::getNumResidences() {
    return numResidences;
}

int Player::getJailTurns() {
    return jailTurns;
}

vector<std::shared_ptr<Cell>> Player::getOwnedProperties() {
    return ownedProperties;
}


void Player::addRollRims() {
    //Get that 1% chance
    int add_cup = rand() % 100 + 1;

    if (add_cup == 1 && totalCups < 4 && getRollRims() < 4) {
        rollRims++;
        //Ahmed implemented a get board global cup counter
        totalCups++;
        cout << "Congrats! You won a Roll Up the Rim cup" << endl;
    }
}

void Player::subtractRollRims() {
    rollRims = rollRims > 0 ?  rollRims-- : 0;
    //Ahmed implemented a get board global cup counter
    totalCups = totalCups > 0 ?  totalCups-- : 0;
    jailTurns = 0;
    timsJail = false;
    jailRolls.clear()
    rollMove();
}


//set Pos after Dice Roll
void Player::rollMove(int num) {
    playerPosn+=num;
}

void Player::subFunds(int num) {
    money -= num;
}

bool Player::getIsBankrupt() {
    return isBankrupt;
}


bool Player::setIsBankrupt(bool bankrupt ) {
    isBankrupt = bankrupt;
}


void  Player::addFunds(int num) {
    money += num;
}

vector<std::shared_ptr<Cell>> Player::getOwnedProperties() {
    return ownedProperties;
}

// As this is a Player, we will only be notified by Cells, so Cells
// contain data with their Info attribute; use accessors.
// Do NOT call State accessors here.
void Player::notify(Subject<Info, State> *whoFrom) {
    Info info = whoFrom->getInfo();
    string cellname = info->cellName;
    // for conveniance, specify typeof building
    // vector<string> academicBuildings = {"AL","ML","ECH","PAS","HH","RCH","DWE","CPH""LHI","BMH","OPT","EV1","EV2","EV3","PHYS","B1","B2","EIT","ESC","C2","MC","DC"};
    // vector<string> residences = {"MKV","UWP","V1","REV"};
    // vector<string> gyms = {"PAC","CIF"};

    if (info.ownable) {
        // Ownable
        
    } else {
        // Non-ownable
        if (cellName == "OCollectOsapSAP") {

        } else if (cellName == "DcTimsLine") {

        } else if (cellName == "GoToTims") {

        } else if (cellName == "CoopFee") {

        } else if (cellName == "Tuiton") {

        } else if (cellName == "SLC") {

        } else if (cellName == "NeedlesHall") {

        }
    }
}

void Player::printAssets() {
    cout << "Name: " << playerName << endl;
    cout << "Character: " << pieceName << endl;

    //Money
    // if (getState().type != StateType::Bankrupt) {
    //     cout << cout << "Money: $" << money << endl;
    // } else {
    //     cout << "Money: " << playerName << " is Bankrupt!" << endl;
    // }
    //@aiden

    //Roll up rim cups
    if (rollRims > 0) {
        cout << "Number Roll up Rim Cups: " << rollRims << endl;
    }

    //properties owned
    for (auto &cell: ownedProperties) {
        cout << "Property: " << cell.getInfo().cellName << " : $" << cell.getInfo().price << endl;
    }
}

//Deals with bankrupt
int Player::playerAssetsWorth() {
    int totalAssets = 0;
    for (auto &cell: ownedProperties) {
        totalAssets += cell.getInfo().price;
    }
    totalAssets += money;
    // if (money <= 0) {
    //     SetState{StateType::Bankrupt};
    // }
    //@aiden
    return totalAssets;
}


// this function is called when:
// 1. Player has enough money to purchase
// 2. Cell is unowned
// 3. Call fn after we have notofied cell that it is being purchased, and cell reponded with "successful" purchase reply.
void Player::purchaseProperties(std::shared_ptr<Cell> c) {
    Info oprop = c->getInfo();

    if (oprop.ownable) {
        if (oprop->ownedBy == nullptr) {
            // Pay
            subFunds(oprop.price);

            // Add to prop vector
            ownedProperties.push_back(c);

            // Increment counter based on property type
            if (oprop.otype == OwnableType::Gym) {
                numGyms++;
            } else if (oprop.otype == OwnableType::Residence) {
                numResidences++;
            } else if (oprop.otype == OwnableType::Academic) {

                // Update FacultyMap
                auto academic = dynamic_cast<AcademicBuildings*>(c.get());
                FacultyMap[std::get<1>(academic_buildings[academic->getFacultyName()])]++;
            }
        }
    }
}



void Player::sellProperty(Player& new_owner, std::shared_ptr<Cell> c) {
    auto oprop = std::dynamic_pointer_cast<OInfo>(c->getInfo());
    if (oprop && oprop->ownedBy == this) {
        // Transfer ownership
        oprop->ownedBy = &new_owner;
        new_owner.ownedProperties.push_back(c);

        //Payment
        new_owner.subFunds(oprop->price);

        // Add funds to seller
        addFunds(oprop->price);

        // Remove from current owner's property vector
        auto it = std::find(ownedProperties.begin(), ownedProperties.end(), c);
        if (it != ownedProperties.end()) {
            ownedProperties.erase(it);
        }

        // Decrement counter based on property type
        if (dynamic_cast<Gym*>(c.get())) {
            numGyms--;
        } else if (dynamic_cast<Residences*>(c.get())) {
            numResidences--;
        } else if (auto academic = dynamic_cast<AcademicBuildings*>(c.get())) {
            // Update FacultyMap
            FacultyMap[std::get<1>(academic_buildings[academic->getFacultyName()])]--;

            // Update new owner's FacultyMap
            new_owner.FacultyMap[std::get<1>(academic_buildings[academic->getFacultyName()])]++;
        }
    }
}





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


    void purchaseProperties(std::shared_ptr<Cell> c);
    void SellProperties(Player *new_owner, std::shared_ptr<Cell> c);
    void BuyProperties(std::shared_ptr<Cell> c);
    void moveMoney();
    void TimsJailTurns(); //Handles jail rolls as well as jail tur
};