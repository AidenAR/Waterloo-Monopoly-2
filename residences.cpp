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
using namespace std;


Residences::Residences(Board &board, std::string name, int pos, int i, int j):
        Cell(board, name, posn, i, j) {}


Residences::Residences~() {}


//Pay Rent
void Residences::payTuition(Player *p) {
    Info info2 = this->getInfo();
    Player *owner = info2.ownedBy;
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


void Residences::mortgage(std::string cellName) {
    Info info3 = this->getInfo();
    Player *owner = info3.ownedBy;
    if (info3.isMortgaged) {
        cout << "mortgaged property already." << endl;
        return;
    }
    if (owner) {
        //give owner half of cost
        int mortgageMoney = resCost * 0.5;
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


void Residences::unMortgage(std::string cellName) {
    Info info4 = this->getInfo();
    Player *owner = info4.ownedBy;
    if (!info4.isMortgaged) {
        cout << "property not mortgaged." << endl;
        return;
    }
    if (owner) {
        if (info4.isMortgaged) {
            // owner pay 60% of cost
            int moneyOwed = (resCost * 0.6);
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


void Residences::notify(Subject<Info, State> &whoNotified);
