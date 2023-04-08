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
using namespace std;

Gyms::Gyms(Board board, int name, int pos, int i, int j):
    Cell(board, name, posn, i, j) {}


Gyms::Gyms~() {}

Board Gyms::getBoard(Gyms& g) {
    return g.board;
}


//Pay Gym Memberswhip
void Gyms::payTuition(Player *p) {
    Info info2 = this->getInfo();
    Player *owner = info2.ownedBy;
    int numGymsOwned = owner->getNumGyms();
    if (numGymsOwned <= 0) {
        cout << "Not owned: No Membership" << endl;
        return;
    }
    if (numGymsOwned == 1) {
        int die1 = getBoard().rollDice();
        int die2 = getBoard().rollDice();
        int sumDie = die1 + die2;
        int membership = oneGym * sumDie;
        cout << "Membership to be paid:$ " << membership << endl;
        owner->addFunds(membership);
        p->subFunds(membership);
        if (p->getMoney() < 0) {
            p->setIsBankrupt(true);
        }
    } else if (numGymsOwned == 2) {
        int die1 = getBoard().rollDice();
        int die2 = getBoard().rollDice();
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


void Gyms::mortgage(std::string cellName) {
    Info info3 = this->getInfo();
    Player *owner = info3.ownedBy;
    if (info3.isMortgaged) {
        cout << "mortgaged property already." << endl;
        return;
    }
    if (owner) {
        //give owner half of cost
        int mortgageMoney = gym_cost * 0.5;
        owner->addFunds(mortgageMoney);
        info3.isMortgaged = true;
        info3.wasSuccesful = true;
        cout << "Successfully mortgaged" << endl;
    } else {
        cout << "Not Owned: unsuccessfully mortgaged" << endl;
        info3.isMortgaged = false;
        info3.wasSuccesful = false;
    }
}


void Gyms::unMortgage(std::string cellName) {
    Info info4 = this->getInfo();
    Player *owner = info4.ownedBy;
    if (!info4.isMortgaged) {
        cout << "property not mortgaged." << endl;
        return;
    }
    if (owner) {
        if (info4.isMortgaged) {
            // owner pay 60% of cost
            int moneyOwed = (gym_cost * 0.6);
            cout << "Pay to unmortgage:$ " << moneyOwed << endl;
            if (owner->getMoney() > moneyOwed) {
                owner->subFunds(moneyOwed);
                info4.isMortgaged = false;
                info4.wasSuccesful = false;
                cout << "Successfully unMortgaged" << endl;
            } else {
                cout << "Not Enough Money to unMortgage" << endl;
            }
        }
    } else {
        cout << "Not Owned: Cannot Unmortgage" << endl;
    }
}



void Gyms::notify(Subject<Info, State> &whoNotified);


