//
// Created by aiden on 03/04/2023.
//

#include "player.h"
#include <string>
#include <algorithm>

using namespace std
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


vector<std::shared_ptr<Cell>> Player::getOwnedProperties() {
    return ownedProperties;
}



// As this is a Player, we will only be notified by Cells, so Cells
// contain data with their Info attribute; use accessors.
// Do NOT call State accessors here.
void notify(Subject<Info, State> *whoFrom) {
    Info *info = whoFrom->getInfo();
    string cellname = info->cellName;
    // for conveniance, specify typeof building
    // vector<string> academicBuildings = {"AL","ML","ECH","PAS","HH","RCH","DWE","CPH""LHI","BMH","OPT","EV1","EV2","EV3","PHYS","B1","B2","EIT","ESC","C2","MC","DC"};
    // vector<string> residences = {"MKV","UWP","V1","REV"};
    // vector<string> gyms = {"PAC","CIF"};

    if (OInfo *oinfo = dynamic_cast<OInfo*>(info)) {
        // Ownable
        if (AcademicBuildings *ab = dynamic_cast<AcademicBuildings *>(whoFrom)) {
            // Academic building
        } else if (Residences *r = dynamic_cast<Residences *>(whoFrom)) {
            // Residences
        } else if (Gyms *g = dynamic_cast<Gyms *>(whoFrom)) {
            // Gyms
        }
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


//set Pos after Dice Roll
void Player::rollMove(int num) {
    playerPosn+=num;
}

void Player::subFunds(int num) {
    money -= num;
}


void  Player::addFunds(int num) {
    money += num;
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


void Player::printAssets() {
    cout << "Name: " << playerName << endl;
    cout << "Character: " << pieceName << endl;

    //Money
    if (getState().type != StateType::Bankrupt) {
        cout << cout << "Money: $" << money << endl;
    } else {
        cout << "Money: " << playerName << " is Bankrupt!" << endl;
    }

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
    if (money <= 0) {
        SetState{StateType::Bankrupt};
    }
    return totalAssets;
}



void Player::purchaseProperties(std::shared_ptr<Cell> c) {
    if (auto oprop = std::dynamic_pointer_cast<OInfo>(c->getInfo())) {
        if (oprop->ownedBy == nullptr) {
            // Pay
            subFunds(oprop->price);

            // Add to prop vector
            ownedProperties.push_back(c);

            // Increment counter based on property type
            if (dynamic_cast<Gym*>(c.get())) {
                numGyms++;
            } else if (dynamic_cast<Residences*>(c.get())) {
                numResidences++;
            } else if (auto academic = dynamic_cast<AcademicBuildings*>(c.get())) {
                // Update property ownership
                oprop->ownedBy = this;

                // Update FacultyMap
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


//Handles jail rolls as well as jail turns
void Player::setJailTurns(int j) {
    jailTurns = j;
}



void setJailTurns(int j);
void Player::TimsJailCell(Player& p) {
    // Check if the player is currently in jail
    if (p.timsJail) {
        // Check if it is the player's third turn in jail
        if (p.getJailTurns() == 3) {
            // Player must pay $50 or use a Roll Up the Rim cup to get out of jail
            if (p.getRollRims() > 0) {
                // Use Roll Up the Rim cup to get out of jail
                p.subtractRollRims();
                p.timsJail = false;
            } else if (p.getMoney() >= 50) {
                // Pay $50 to get out of jail
                p.subFunds(50);
                p.timsJail = false;
            } else {
                // Player doesn't have enough money to get out of jail
                p.timsJail = true;
            }
        } else {
            //in main or board???
            // Player must roll the dice to try to get doubles
            int diceRoll1 = rollDice();
            int diceRoll2 = rollDice();
            if (diceRoll1 == diceRoll2) {
                // Player rolled doubles and gets out of jail
                p.setJailTurns(0);
                p.timsJail = false;
            } else {
                // Player did not roll doubles
                p.setJailTurns(p.getJailTurns() + 1);
                p.timsJail = true;
            }
        }
    } else {
        // Player is not in jail
        p.timsJail = false;
    }
}
