//
// Created by aiden on 04/04/2023.
//

#include "gyms.h"
#include "ownable.h"
#include <unordered_map>
#include "player.h"
#include "state.h"
#include "observer.h"
#include "subject.h"
#include "board.h"
#include <iostream>
using namespace std;

Gyms::Gyms(Board &board, int name, int pos, int i, int j) :
    Cell(board, name, posn, i, j) {}


Gyms::~Gyms() {}

Board Gyms::getBoard(Gyms& g) {
    return g.board;
}


//Pay Gym Memberswhip
void Gyms::payTuition(Player *p) {
    int numGymsOwned = getOwnedBy()->getNumGyms();
    if (numGymsOwned <= 0) {
        cout << "Not owned: No Membership" << endl;
        return;
    }
    if (numGymsOwned == 1) {
        int die1 = getBoard().rollDice()[0];
        int die2 = getBoard().rollDice()[1];
        int sumDie = die1 + die2;
        int membership = oneGym * sumDie;
        cout << "Membership to be paid:$ " << membership << endl;
        getOwnedBy()->addFunds(membership);
        p->subFunds(membership);
        if (p->getMoney() < 0) {
            p->setIsBankrupt(true);
        }
    } else if (numGymsOwned == 2) {
        int die1 = getBoard(*this).rollDice()[0];
        int die2 = getBoard(*this).rollDice()[1];
        int sumDie = die1 + die2;
        int membershipTwo = twoGym * sumDie;
        cout << "Membership to be paid:$ " << membershipTwo << endl;
        getOwnedBy()->addFunds(membershipTwo);
        p->subFunds(membershipTwo);
        if (p->getMoney() < 0) {
            p->setIsBankrupt(true);
        }
    }
}


void Gyms::mortgage() {
    // string cellName = setcellName();
    // Player *owner = setownedBy();
    if (getMortgaged()) {
        cout << "mortgaged property already." << endl;
        return;
    }
    if (owner) {
        //give owner half of cost
        int mortgageMoney = gym_cost * 0.5;
        owner->addFunds(mortgageMoney);
        setMortgaged(true);
        setSuccesful(true);
        cout << "Successfully mortgaged" << endl;
    } else {
        cout << "Not Owned: unsuccessfully mortgaged" << endl;
        setMortgaged(false);
        setSuccesful(false);
    }
}


void Gyms::unMortgage() {
    if (!getMortgaged()) {
        cout << "property not mortgaged." << endl;
        return;
    }
    if (getOwnedBy()) {
        if (getMortgaged()) {
            // owner pay 60% of cost
            int moneyOwed = (gym_cost * 0.6);
            cout << "Pay to unmortgage:$ " << moneyOwed << endl;
            if (getOwnedBy()->getMoney() > moneyOwed) {
                getOwnedBy()->subFunds(moneyOwed);
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



void Gyms::notify(std::shared_ptr<Subject<Info, State>> whoFrom) {
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
        this->setOwnedBy(state.newOwner);
        this->setSuccesful(true);

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
        // Player side things are handlded by player.cc
        setOwnedBy(state.newOwner);
        break;
    case StateType::Landed:
        if (getOwnedBy() != whoFrom) {
            payTuition(whoFrom);
        }
        break;
    default:
        return;
    }

    notifyObservers();
    
}