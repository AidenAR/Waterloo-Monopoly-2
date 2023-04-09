//
// Created by aiden on 04/04/2023.
//

#include "gyms.h"
#include "ownable.h"
#include <unordered_map>
#include "info.h"
#include "player.h"
#include "state.h"
#include "info.h"
#include "observer.h"
#include "subject.h"
#include "board.h"
#include <iostream>
using namespace std;

Gyms::Gyms(Board &board, std::string name, int pos, int i, int j, bool ownable, OwnableType otype, int price) :
    Ownable(board, name, posn, i, j, ownable, otype, price) {}


Gyms::~Gyms() {}

Board Gyms::getBoard(Gyms& g) {
    return g.board;
}


//Pay Gym Memberswhip
void Gyms::payTuition(Player *p) {
    Player *owner = info.ownedBy;
    int numGymsOwned = owner->getNumGyms();
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
        owner->addFunds(membership);
        p->subFunds(membership);
        if (p->getMoney() < 0) {
            p->setIsBankrupt(true);
        }
    } else if (numGymsOwned == 2) {
        int die1 = getBoard().rollDice()[0];
        int die2 = getBoard().rollDice()[1];
        int sumDie = die1 + die2;
        int membershipTwo = twoGym * sumDie;
        cout << "Membership to be paid:$ " << membershipTwo << endl;
        owner->addFunds(membershipTwo);
        p->subFunds(membershipTwo);
        if (p->getMoney() < 0) {
            p->setIsBankrupt(true);
        }
    }
}


void Gyms::mortgage() {
    string cellName = info.cellName;
    Player *owner = info.ownedBy;
    if (info.isMortgaged) {
        cout << "mortgaged property already." << endl;
        return;
    }
    if (owner) {
        //give owner half of cost
        int mortgageMoney = gym_cost * 0.5;
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


void Gyms::unMortgage() {
    string cellName = info.cellName;
    Player *owner = info.ownedBy;
    if (!info.isMortgaged) {
        cout << "property not mortgaged." << endl;
        return;
    }
    if (owner) {
        if (info.isMortgaged) {
            // owner pay 60% of cost
            int moneyOwed = (gym_cost * 0.6);
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
        // Player side things are handlded by player.cc
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