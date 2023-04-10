//
// Created by aiden on 03/04/2023.
//

#include "ownable.h"
#include <string>
#include <iostream>
#include "player.h"
#include "cell.h"

using namespace std;


Ownable::Ownable(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price) :
    Cell(board, name, posn, i, j, ownable, otype, price) {}

string Ownable::getFacultyName(const std::string& buildingName) {
    for (const auto& building : academic_buildings) {
        if (buildingName == building.first) {
            return std::get<0>(building.second);
        }
    }
    return "Building not found.";
}


void Ownable::buy(Player *p) {
    if (p->getMoney() < price) {
        cout << "Not enough funds" << endl;
        return;
    }
    p->subFunds(getPrice());
    setOwnedBy(p);
    //p->addProperty(*this);
    cout << "Bought " << getName() << " for " << price << endl;
}

void Ownable::auction() {
    cout << "Auctioning " << getName() << endl;
    int highestBid = 0;
    Player *highestBidder = nullptr;
    for (auto &player : board.getPlayerList()) {
        if (player->getMoney() > highestBid) {
            highestBid = player->getMoney();
            highestBidder = player.get();
        }
    }
    if (highestBidder) {
        highestBidder->subFunds(highestBid);
        setOwnedBy(highestBidder);
        //highestBidder->addProperty(*this);
        cout << "Auction won by " << highestBidder->getName() << " for " << highestBid << endl;
    }
}

int Ownable::improvementCost() {
    if (otype != OwnableType::Academic) {
        return 0;
    } else {
        return std::get<2>(academic_buildings.find(getName())->second);
    }
}
void Ownable::sellImprovement() {
    if (otype != OwnableType::Academic) {
        return;
    }

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
void Ownable::buyImprovement() {
    if (otype != OwnableType::Academic) {
        return;
    }
    
    Player *owner = getOwnedBy();
    string cName = getName();
    if (isMortgage) {
        cout << "mortgaged property: No improvements Allowed" << endl;
        return;
    }
    string facName = getFacultyName(cName);
    if (owner) {
        owner->partMonopoly();
        if (getOwnedBy()->FacultyMap[facName].second && getImproveCount() < 5) {
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
void Ownable::payTuition(Player *p) {
    if (otype == OwnableType::Academic) {
        Player *owner = getOwnedBy();
        string cName = getName();
        string facName = getFacultyName(cName);
        if (owner) {
            owner->partMonopoly();
            if (getOwnedBy()->FacultyMap[facName].second && getImproveCount() == 0) {
                //owner has a monopoly and < 5 built so can buy improvement
                //tuple w costs
                auto building = academic_buildings.find(cName)->second;
                //double tuition at 0
                owner->addFunds((std::get<3>(building)) * 2);
                p->subFunds((std::get<3>(building)) * 2);
                if (p->getMoney() < 0) {
                    //TODO p->setIsBankrupt(true);
                    //.......what happens after call fn
                }
            } else {
                auto building = academic_buildings.find(cName)->second;
                //reg tuition
                int num = getImproveCount();
                int num1;
            switch (num) {
                case 0:
                    num1 = std::get<3>(building);
                    break;
                case 1:
                    num1 = std::get<4>(building);
                    break;
                case 2:
                    num1 = std::get<5>(building);
                    break;
                case 3:
                    num1 = std::get<6>(building);
                    break;
                case 4:
                    num1 = std::get<7>(building);
                    break;
                case 5:
                    num1 = std::get<8>(building);
                    break;
            }
                owner->addFunds(num1);
                p->subFunds(num1);
                //make call to Bankrupt
                //Hassan pls
                if (p->getMoney() < 0) {
                    //p->setIsBankrupt(true);
                    //.......what happens after call fn
                }
            }
        } else {
            cout << "Not owned: No Tuition needed" << endl;
            return;
        }
        
    } else if (otype == OwnableType::Residence) {
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
        
    } else if (otype == OwnableType::Gym) {
        int numGymsOwned = getOwnedBy()->getNumGyms();
        if (numGymsOwned <= 0) {
            cout << "Not owned: No Membership" << endl;
            return;
        }
        if (numGymsOwned == 1) {
            int die1 = board.rollDice()[0];
            int die2 = board.rollDice()[1];
            int sumDie = die1 + die2;
            int membership = oneGym * sumDie;
            cout << "Membership to be paid:$ " << membership << endl;
            getOwnedBy()->addFunds(membership);
            p->subFunds(membership);
            if (p->getMoney() < 0) {
                // TODO p->setIsBankrupt(true);
            }
        } else if (numGymsOwned == 2) {
            int die1 = board.rollDice()[0];
            int die2 = board.rollDice()[1];
            int sumDie = die1 + die2;
            int membershipTwo = twoGym * sumDie;
            cout << "Membership to be paid:$ " << membershipTwo << endl;
            getOwnedBy()->addFunds(membershipTwo);
            p->subFunds(membershipTwo);
            if (p->getMoney() < 0) {
                //TODO p->setIsBankrupt(true);
            }
        }
    } else {
        return;
    }
}
void Ownable::mortgage() {
    if (otype == OwnableType::Academic) {
        string cellName = getName();
        
        Player *owner = getOwnedBy();
        if (getMortgaged()) {
            cout << "mortgaged property already." << endl;
            return;
        }
        if (owner != nullptr) {
            //sell off all improvements if existing
            if (getImproveCount() > 0) {
                for (int i = 0; i < getImproveCount(); i++) {
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
    } else if (otype == OwnableType::Residence) {
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
        
    } else if (otype == OwnableType::Gym) {
        if (getMortgaged()) {
        cout << "mortgaged property already." << endl;
        return;
        }
        if (getOwnedBy()) {
            //give owner half of cost
            int mortgageMoney = gym_cost * 0.5;
            getOwnedBy()->addFunds(mortgageMoney);
            setMortgaged(true);
            setSuccesful(true);
            cout << "Successfully mortgaged" << endl;
        } else {
            cout << "Not Owned: unsuccessfully mortgaged" << endl;
            setMortgaged(false);
            setSuccesful(false);
        }
        
    } else {
        return;
    }
}




void Ownable::unMortgage() {
    if (otype == OwnableType::Academic) {
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
    } else if (otype == OwnableType::Residence || otype == OwnableType::Gym) {
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
    } else {
        return;
    }
}



void Ownable::event(Player *p) {
    
    cout << "recieved notification. maybe intended for me idk. cellName: " << getName() << endl;
    cout << "welcome to: " << getName() << endl;

    if (getOwnedBy() != nullptr) {
        cout << "owned by: " << getOwnedBy() << endl;
        payTuition(p);
    } else if (getOwnedBy() == nullptr && getPrice() > p->getMoney()) {
        cout << "not owned by anyone, but you are broke" << endl;
        auction();
    } else if (getOwnedBy() == nullptr){
        cout << "Do you want to buy this or not? (y/n)" << endl;
        string input;
        cin >> input;
        if (input == "y") {
            buy(p);
        } else {
            auction();
        }

    } else {
        cout << "you own this property" << endl;
    }
        
}

void Ownable::setOwner(Player *p) {
    setOwnedBy(p);
}


