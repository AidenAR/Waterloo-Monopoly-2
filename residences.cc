//
// Created by aiden on 03/04/2023.
//

#include "residences.h"
#include "ownable.h"
#include <unordered_map>
#include "player.h"
#include "state.h"
#include "observer.h"
#include "subject.h"
#include <iostream>
using namespace std;


Residences::Residences(Board &board, std::string name, int pos, int i, int j, bool ownable, OwnableType otype, int price) :
    Ownable(board, name, posn, i, j, ownable, otype, price) {}


Residences::~Residences() {}


//Pay Rent
void Residences::payTuition(Player *p) {
    Player *owner = getOwnedBy();
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
            // p->setIsBankrupt(true);
        }
    } else if (numResOwned == 2) {
        cout << "Rent to be paid:$ " << twoResRent << endl;
        owner->addFunds(twoResRent);
        p->subFunds(twoResRent);
        if (p->getMoney() < 0) {
            // p->setIsBankrupt(true);
        }
    } else if (numResOwned == 3) {
        cout << "Rent to be paid:$ " << threeResRent << endl;
        owner->addFunds(threeResRent);
        p->subFunds(threeResRent);
        if (p->getMoney() < 0) {
            // p->setIsBankrupt(true);
        }
    } else if (numResOwned == 4) {
        cout << "Rent to be paid:$ " << fourResRent << endl;
        owner->addFunds(fourResRent);
        p->subFunds(fourResRent);
        if (p->getMoney() < 0) {
            // p->setIsBankrupt(true);
        }
    }
}


void Residences::mortgage() {
    string cellName = getName();
    if (getMortgaged()) {
        cout << "mortgaged property already." << endl;
        return;
    }
    if (getOwnedBy() != nullptr) {
        //give owner half of cost
        int mortgageMoney = resCost * 0.5;
        getOwnedBy()->addFunds(mortgageMoney);
        setMortgaged(true);
        setSuccesful(true);
        cout << "Successfully mortgaged " << cellName << endl;
    } else {
        cout << "Not Owned: unsuccessfully mortgaged " << cellName << endl;
        setMortgaged(false);
        setSuccesful(false);
    }
}


void Residences::unMortgage() {
    string cellName = getName();
    Player *owner = getOwnedBy();
    if (!getMortgaged()) {
        cout << "property not mortgaged." << endl;
        return;
    }
    if (owner) {
        if (getMortgaged()) {
            // owner pay 60% of cost
            int moneyOwed = (resCost * 0.6);
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
            break;
        }
        setOwnedBy(state.newOwner);
        setSuccesful(true);

        break;
    case StateType::Mortgage:
        if (this->getMortgaged() || getOwnedBy() != whoFrom.get()) {
            setSuccesful(false);
            break;
        }

        mortgage();

        break;
    case StateType::Unmortgage:
        if (this->getMortgaged() || getOwnedBy() != whoFrom.get()) {
            setSuccesful(false);
            break;
        }

        unMortgage();
        break;
    case StateType::SellTo:
        // Fund transactions are handlded by player.cc
        setOwnedBy(state.newOwner);
        break;
    case StateType::Landed:
        if (getOwnedBy() != whoFrom.get()) {
            payTuition(dynamic_cast<Player *>(whoFrom.get()));
        }
        break;
    default:
        return;
    }

    notifyObservers();
    
}