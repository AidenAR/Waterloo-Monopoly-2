//
// Created by aiden on 03/04/2023.
//

#include "AcademicBuildings.h"
#include "ownable.h"
#include <unordered_map>
#include "info.h"
#include "player.h"
#include "state.h"
#include "info.h"
#include "observer.h"
#include "subject.h"
#include <tuple>
#include <iostream>
using namespace std;

//Bankrupt fn  implemented:
//Hassan check notifs

AcademicBuildings::AcademicBuildings(Board &board, std::string name, int pos, int i, int j) :
    Cell(board, name, posn, i, j) {}

AcademicBuildings::~AcademicBuildings() {}


std::string AcademicBuildings::getFacultyName(const std::string& buildingName) {
    for (const auto& building : academic_buildings) {
        if (buildingName == building.first) {
            return std::get<0>(building.second);
        }
    }
    return "Building not found.";
}


void AcademicBuildings::buyImprovement() {
    Info info2 = this->getInfo();
    Player *owner = info2.ownedBy;
    string cName = info2.cellName;
    if (isMortgage) {
        cout << "mortgaged property: No improvements Allowed" << endl;
        return;
    }
    string facName = getFacultyName(cName);
    if (owner) {
        owner->partMonopoly();
        if (FacultyMap[facName].second && info2.improveCount < 5) {
            //owner has a monopoly and < 5 built so can buy improvement
            //tuple w costs
            auto building = academic_buildings.find(cName)->second;
            //get cost of curr improvement and subtract
            owner->subFunds(std::get<2>(building));
            if (info2.improveCount < 4) {
                cout << "Installed a Bathroom" << endl;
            } else {
                cout << "Installed a Cafeteria" << endl;
            }
            info2.improveCount++;
        }
    } else {
        cout << "No Ownership:No Improvements allowed" << endl;
    }
}


void AcademicBuildings::sellImprovement() {
    int improvement = info.improveCount;

    Player *owner = info.ownedBy;
    string cName = info.cellName;
    if (owner == nullptr) {
        cout << "Not owned: No Improvements to sell" << endl;
        return;
    }
    if (info.improveCount < 0) {
        cout << "No Improvements to sell" << endl;
        return;
    }
    //tuple w costs
    auto building = academic_buildings.find(cName)->second;
    //get cost of curr improvement and subtract
    owner->addFunds((std::get<2>(building)) * 0.5);
    cout << "Sold Improvement: " << improvement << endl;
    if (info.improveCount < 4) {
        cout << "Sold a Bathroom" << endl;
    } else {
        cout << "Sold a Cafeteria" << endl;
    }
    cout << "Received:$" << ((std::get<2>(building)) * 0.5) << endl;
    info.improveCount--;
}


void AcademicBuildings::payTuition(Player *p) {
    Player *owner = info.ownedBy;
    string cName = info.cellName;
    string facName = getFacultyName(cName);
    if (owner) {
        owner->partMonopoly();
        if (FacultyMap[facName].second && info.improveCount == 0) {
            //owner has a monopoly and < 5 built so can buy improvement
            //tuple w costs
            auto building = academic_buildings.find(cName)->second;
            //double tuition at 0
            owner->addFunds((std::get<3>(building)) * 2);
            p->subFunds((std::get<3>(building)) * 2);
            if (p->getMoney() < 0) {
                p->setIsBankrupt(true);
                //.......what happens after call fn
            }
        } else {
            auto building = academic_buildings.find(cName)->second;
            //reg tuition
            owner->addFunds(std::get<3 + info.improveCount>(building));
            p->subFunds(std::get<3 + info.improveCount>(building));
            //make call to Bankrupt
            //Hassan pls
            if (p->getMoney() < 0) {
                p->setIsBankrupt(true);
                //.......what happens after call fn
            }
        }
    } else {
        cout << "Not owned: No Tuition needed" << endl;
        return;
    }
}


void AcademicBuildings::mortgage() {
    string cellName = info.cellName;
    
    Player *owner = info.ownedBy;
    if (info.isMortgaged) {
        cout << "mortgaged property already." << endl;
        return;
    }
    if (owner) {
        //sell off all improvements if existing
        if (info.improveCount > 0) {
            for (int i = 0; i < info.improveCount; i++) {
                this->sellImprovement(i);
            }
        }
        //give owner half of cost
        //tuple w costs
        auto building = academic_buildings.find(cellName)->second;
        owner->addFunds((std::get<1>(building)) * 0.5);

        info.isMortgaged = true;
        info.wasSuccesful = true;
        cout << "Successfully mortgaged" << endl;
    } else {
        cout << "Not Owned: unsuccessfully mortgaged" << endl;
        info.isMortgaged = false;
        info.wasSuccesful = false;
    }
}


void AcademicBuildings::unMortgage() {
    string cellName = info.cellName;

    Info info = this->getInfo();
    Player *owner = info.ownedBy;
    if (!info.isMortgaged) {
        cout << "property not mortgaged." << endl;
        info.wasSuccesful = false;
        return;
    }
    if (owner) {
        if (info.isMortgaged) {
            //give owner half of cost
            //tuple w costs
            auto building = academic_buildings.find(cellName)->second;
            int moneyOwed = ((std::get<1>(building)) * 0.6);
            cout << "Pay to unmortgage:$ " << moneyOwed << endl;
            if (owner->getMoney() > moneyOwed) {
                owner->subFunds(moneyOwed);
                info.isMortgaged = false;
                info.wasSuccesful = false;
                cout << "Successfully unMortgaged" << endl;
            } else {
                cout << "Not Enough Money to unMortgage" << endl;
            }
        }
    } else {
        cout << "Not Owned: Cannot Unmortgage" << endl;
    }
}



void AcademicBuildings::notify(std::shared_ptr<Subject<Info, State>> whoFrom) {
    State state = *(whoFrom->getState());
    StateType type = state.type;
    
    // cellName != "" means notif directed for cell which is not the one Player is on, so gotta check if cellName matches.
    if (!((state.cellName == this->name) || (state.playerPosn == this->posn))) {
        return;
    }

    // As cellName matches, means notif directed for this cell. 
    switch (type)
    {
    case StateType::Purchase:
        if (info.ownedBy != nullptr) {
            info.wasSuccesful = false;
            break;
        }
        this->info.ownedBy = state.newOwner;
        this->info.wasSuccesful = true;

        break;
    case StateType::Mortgage:
        if (this->info.isMortgaged || info.ownedBy != whoFrom.get()) {
            info.wasSuccesful = false;
            break;
        }

        mortgage();

        break;
    case StateType::Unmortgage:
        if (this->info.isMortgaged || info.ownedBy != whoFrom.get()) {
            info.wasSuccesful = false;
            break;
        }

        unMortgage();
        break;
    case StateType::SellTo:
        // Fund transactions are handlded by player.cc
        info.ownedBy = state.newOwner;
        break;
    case StateType::SellImprovement:
        
        sellImprovement();
        break;
    case StateType::Landed:
        if (info.ownedBy != whoFrom) {
            payTuition(whoFrom);
        }
        break;
    default:
        return;
    }

    notifyObservers();
    
}












//add to player.h and player.cc

/*
const int NumArts1 = 2;
const int NumArts3 = 3;
const int NumEng = 3;
const int NumHealth = 3;
const int NumEnv = 3;
const int NumSci1 = 3;
const int NumSci2 = 3;
const int NumMath = 2;

bool Player:: partMonopoly(std::unordered_map<std::string) {
    if ((FacultyMap["Arts1"] == NumArts1) ||
    (FacultyMap["Arts2"] == NumArts3) ||
    (FacultyMap["Eng"] == NumEng) ||
    (FacultyMap["Health"] == NumHealth) ||
    (FacultyMap["Env"] == NumEnv) ||
    (FacultyMap["Sci1"] == NumSci1) ||
    (FacultyMap["Sci2"] == NumSci2) ||
    (FacultyMap["Math"] == NumMath)) {
        return true;
    }
    return false;
}
*/


std::unordered_map<std::string, std::pair<int, bool>> FacultyMap =
        {{"Arts1", {0, false}}, {"Arts2", {0, false}}, {"Eng", {0, false}},
         {"Health", {0, false}}, {"Env", {0, false}}, {"Sci1", {0, false}},
         {"Sci2", {0, false}}, {"Math", {0, false}}};

const int NumArts1 = 2;
const int NumArts3 = 3;
const int NumEng = 3;
const int NumHealth = 3;
const int NumEnv = 3;
const int NumSci1 = 3;
const int NumSci2 = 3;
const int NumMath = 2;

void Player:: partMonopoly() {
    if (FacultyMap["Arts1"].first == NumArts1) {
        FacultyMap["Arts1"].second = true;
    }
    if (FacultyMap["Arts2"].first == NumArts3) {
        FacultyMap["Arts2"].second = true;
    }
    if (FacultyMap["Eng"].first == NumEng) {
        FacultyMap["Eng"].second = true;
    }
    if (FacultyMap["Health"].first == NumHealth) {
        FacultyMap["Health"].second = true;
    }
    if (FacultyMap["Env"].first == NumEnv) {
        FacultyMap["Env"].second = true;
    }
    if (FacultyMap["Sci1"].first == NumSci1) {
        FacultyMap["Sci1"].second = true;
    }
    if (FacultyMap["Sci2"].first == NumSci2) {
        FacultyMap["Sci2"].second = true;
    }
    if (FacultyMap["Math"].first == NumMath) {
        FacultyMap["Math"].second = true;
    }
}
