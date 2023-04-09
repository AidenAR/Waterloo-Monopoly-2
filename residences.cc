//
// Created by aiden on 03/04/2023.
//

#include "residences.h"
#include "ownable.h"
#include <unordered_map>
#include "info.h"
#include "player.h"
#include "state.h"
#include "info.h"
#include "observer.h"
#include "subject.h"
#include <iostream>
using namespace std;


Residences::Residences(Board &board, std::string name, int pos, int i, int j, bool ownable, OwnableType otype, int price) :
    Ownable(board, name, posn, i, j, ownable, otype, price) {}


Residences::~Residences() {}


//Pay Rent
void Residences::payTuition(Player *p) {
    Player *owner = info.ownedBy;
    int numResOwned = owner->getNumResidences();
    if (numResOwned <= 0) {
        cout << "Not owned: No Rent" << endl;
        return;
    }
    if (numResOwned == 1) {
        cout << "Rent to be paid:$ " << oneResRent << endl;
        owner->addFunds(oneResRent);
        p->subFunds(oneResRent);
        if (p->getMoney() < 0) {
            p->setIsBankrupt(true);
        }
    } else if (numResOwned == 2) {
        cout << "Rent to be paid:$ " << twoResRent << endl;
        owner->addFunds(twoResRent);
        p->subFunds(twoResRent);
        if (p->getMoney() < 0) {
            p->setIsBankrupt(true);
        }
    } else if (numResOwned == 3) {
        cout << "Rent to be paid:$ " << threeResRent << endl;
        owner->addFunds(threeResRent);
        p->subFunds(threeResRent);
        if (p->getMoney() < 0) {
            p->setIsBankrupt(true);
        }
    } else if (numResOwned == 4) {
        cout << "Rent to be paid:$ " << fourResRent << endl;
        owner->addFunds(fourResRent);
        p->subFunds(fourResRent);
        if (p->getMoney() < 0) {
            p->setIsBankrupt(true);
        }
    }
}


void Residences::mortgage() {
    string cellName = info.cellName;
    Player *owner = info.ownedBy;
    if (info.isMortgaged) {
        cout << "mortgaged property already." << endl;
        return;
    }
    if (owner) {
        //give owner half of cost
        int mortgageMoney = resCost * 0.5;
        owner->addFunds(mortgageMoney);
        info.isMortgaged = true;
        info.wasSuccesful = true;
        cout << "Successfully mortgaged" << endl;
    } else {
        cout << "Not Owned: unsuccessfully mortgaged" << endl;
        info.isMortgaged = false;
        info.wasSuccesful = false;
    }
}


void Residences::unMortgage() {
    string cellName = info.cellName;
    Player *owner = info.ownedBy;
    if (!info.isMortgaged) {
        cout << "property not mortgaged." << endl;
        return;
    }
    if (owner) {
        if (info.isMortgaged) {
            // owner pay 60% of cost
            int moneyOwed = (resCost * 0.6);
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