//
// Created by aiden on 03/04/2023.
//

#include "AcademicBuildings.h"
#include "ownable.h"
#include <unordered_map>
#include "player.h"
#include "state.h"
#include "observer.h"
#include "subject.h"
#include <tuple>
#include <iostream>
using namespace std;

//Bankrupt fn  implemented:
//Hassan check notifs

AcademicBuildings::AcademicBuildings(Board &board, std::string name, int pos, int i, int j, bool ownable, OwnableType otype, int price) :
    Ownable(board, name, posn, i, j, ownable, otype, price) {}

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
    Player *owner = getOwnedBy();
    string cName = getName();
    if (isMortgage) {
        cout << "mortgaged property: No improvements Allowed" << endl;
        return;
    }
    string facName = getFacultyName(cName);
    if (owner) {
        owner->partMonopoly();
        if (FacultyMap[facName].second && getImproveCount() < 5) {
            //owner has a monopoly and < 5 built so can buy improvement
            //tuple w costs
            auto building = academic_buildings.find(cName)->second;
            //get cost of curr improvement and subtract
            owner->subFunds(std::get<2>(building));
            if (getImproveCount() < 4) {
                cout << "Installed a Bathroom" << endl;
            } else {
                cout << "Installed a Cafeteria" << endl;
            }
            setImproveCount( (getImproveCount() + 1) );
        }
    } else {
        cout << "No Ownership:No Improvements allowed" << endl;
    }
}


void AcademicBuildings::sellImprovement() {
    getImproveCount();

    Player *owner = getOwnedBy();
    string cName = getName();
    if (owner == nullptr) {
        cout << "Not owned: No Improvements to sell" << endl;
        return;
    }
    if (getImproveCount() < 0) {
        cout << "No Improvements to sell" << endl;
        return;
    }
    //tuple w costs
    auto building = academic_buildings.find(cName)->second;
    //get cost of curr improvement and subtract
    owner->addFunds((std::get<2>(building)) * 0.5);
    cout << "Sold Improvement: " << getImproveCount() << endl;
    if (getImproveCount() < 4) {
        cout << "Sold a Bathroom" << endl;
    } else {
        cout << "Sold a Cafeteria" << endl;
    }
    cout << "Received:$" << ((std::get<2>(building)) * 0.5) << endl;
    setImproveCount(getImproveCount() - 1);
}


void AcademicBuildings::payTuition(Player *p) {
    Player *owner = getOwnedBy();
    string cName = getName();
    string facName = getFacultyName(cName);
    if (owner) {
        owner->partMonopoly();
        if (FacultyMap[facName].second && getImproveCount() == 0) {
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
            owner->addFunds(std::get<3 + getImproveCount()>(building));
            p->subFunds(std::get<3 + getImproveCount()>(building));
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
    string cellName = getName();
    
    Player *owner = getOwnedBy();
    if (getMortgaged()) {
        cout << "mortgaged property already." << endl;
        return;
    }
    if (owner) {
        //sell off all improvements if existing
        if (getImproveCount() > 0) {
            for (int i = 0; i < info.improveCount; i++) {
                this->sellImprovement();
            }
        }
        //give owner half of cost
        //tuple w costs
        auto building = academic_buildings.find(cellName)->second;
        owner->addFunds((std::get<1>(building)) * 0.5);

        setMortgaged(true);
        setSuccesful(true);
        cout << "Successfully mortgaged" << endl;
    } else {
        cout << "Not Owned: unsuccessfully mortgaged" << endl;
        setMortgaged(false);
        setSuccesful(false);
    }
}


void AcademicBuildings::unMortgage() {
    string cellName = getName();

    Player *owner = getOwnedBy();
    if (!getMortgaged()) {
        cout << "property not mortgaged." << endl;
        setSuccesful(false);
        return;
    }
    if (owner) {
        if (getMortgaged()) {
            //give owner half of cost
            //tuple w costs
            auto building = academic_buildings.find(cellName)->second;
            int moneyOwed = ((std::get<1>(building)) * 0.6);
            cout << "Pay to unmortgage:$ " << moneyOwed << endl;
            if (owner->getMoney() > moneyOwed) {
                owner->subFunds(moneyOwed);
                setMortgaged(false);
                setSuccesful(false);
                cout << "Successfully unMortgaged" << endl;
            } else {
                cout << "Not Enough Money to unMortgage" << endl;
            }
        }
    } else {
        cout << "Not Owned: Cannot Unmortgage" << endl;
    }
}



void AcademicBuildings::notify(std::shared_ptr<Subject<State>> whoFrom) {
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
        if (getOwnedBy() != nullptr) {
            setSuccesful(false);
            notifyObservers();
            break;
        }
        setOwnedBy(state.newOwner);
        setSuccesful(true);
        notifyObservers();
        break;
    case StateType::Mortgage:
        if (getMortgaged()) return;
        if (getOwnedBy() != whoFrom.get()) return;
        if (getName() != state.cellName) return;

        mortgage();
        break;
    case StateType::Unmortgage:
        if (getMortgaged()) return;
        if (getOwnedBy() != whoFrom.get()) return;
        if (getName() != state.cellName) return;

        unMortgage();
        break;
    case StateType::SellTo:
        // Fund transactions are handlded by player.cc
        setOwnedBy(state.newOwner);
        setSuccesful(true);
        notifyObservers();
        break;
    case StateType::SellImprovement:
        if (state.cellName != getName()) return;
        sellImprovement();
        break;
    case StateType::AddImprovement:
        if (state.cellName != getName()) return;
        buyImprovement();
        break;
    case StateType::Landed:
        if (getOwnedBy() == nullptr) {
            // Player now must deicde whether to auction or purchase.
            // Send notif back to player s they can decide.
        } else if (getOwnedBy() != whoFrom.get()) {
            payTuition(whoFrom);
        } // Else we own cell, nothing to do.
        break;
    default:
        return;
    }
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

/*
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
8/