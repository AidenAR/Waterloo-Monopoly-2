//
// Created by aiden on 03/04/2023.
//

#include "player.h"
#include <string>
#include <algorithm>

using namespace std;
#include <cstdlib>
#include <iostream>
#include <vector>
#include "board.h"

class State;
class Info;
class Board;


Player::Player(string playerName, char pieceName, int money, int rollRims, int playerPosn):
    playerName{playerName}, pieceName{pieceName},
    money{startingMoney}, rollRims{rollRims},
    playerPosn{0}, numGyms{0}, numResidences{0},
    jailTurns{0}, timsJail{false} {
    vector<int> jailRolls{0};
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


void Player::setState(State state) {
    this->state = state;
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

void Player::subtractRollRims() {
    rollRims = rollRims > 0 ?  rollRims-- : 0;
    //Ahmed implemented a get board global cup counter
    totalCups = totalCups > 0 ?  totalCups-- : 0;
    jailTurns = 0;
    timsJail = false;
    jailRolls.clear()
    rollMove();
}


// moveForward() will move player forward by one; intention is, if we need to move 5, we call moveForward() 5 times.
// This will notify all observers that Player is moving forward by 1 (Move notif). 
// On the 5th moving, specify that player has landed on that spot with landed=true (Landed notif).
void Player::moveForward(bool landed = false) {
    playerPosn++;

    State newS = State();
    newS.type = landed ? StateType::Landed : StateType::Move;
    newS.playerPosn = playerPosn;

    this->notifyObservers();
}

void Player::subFunds(int num) {
    money -= num;
}

void  Player::addFunds(int num) {
    money += num;
}

// As this is a Player, we will only be notified by Cells, so Cells contain data with their Info attribute; use Info accessors.
// Do NOT call State accessors here.
void Player::notify(std::shared_ptr<Subject<Info, State>> whoFrom) {
    Info *info = whoFrom->getInfo();
    this->cellInfo = info;

    string cellName = info->cellName;
    
    cout << "You landed on:" << endl;
    cout << cellName << endl;

    // for convenience:
    // vector<string> academicBuildings = {"AL","ML","ECH","PAS","HH","RCH","DWE","CPH""LHI","BMH","OPT","EV1","EV2","EV3","PHYS","B1","B2","EIT","ESC","C2","MC","DC"};
    // vector<string> residences = {"MKV","UWP","V1","REV"};
    // vector<string> gyms = {"PAC","CIF"};

    if (info->ownable) {
        // Ownable

        if (info->ownedBy == nullptr) {
            cout << "Cell owned by nobody, would you like to purchase for: " << info->price << "\n[y/n]" << endl;
            string response;
            cin >> response; 
            if (response == "y") {
                attemptBuyProperty(whoFrom);
            } else {
                // TODO:
                // AUCTION DAT!!!
            }
        }

        OwnableType otype = info->otype;
        if (otype == OwnableType::Academic) {
            // Academic
            // if they are not owned by us, then we must pay money to owner.s
        } else if (otype == OwnableType::Residence) {
            // Residence
        } else if (otype == OwnableType::Gym) {
            // Gym
        } 
        
    } else {
        // Non-ownable
        if (cellName == "OCollectOsapSAP") {
            addFunds(200);
        } else if (cellName == "DcTimsLine") {
            if (getTimsJail()) {
                if (getJailTurns() == 3) {
                    cout << "You have been in jail for 3 turns, you must pay $50 to get out" << endl;
                    subFunds(50);
                    subtractRollRims();
                } else if (getRollRims() > 0) {
                    cout << "Do you want to use a roll up the rim cup to get out of jail?[y/n]" << endl;
                    string response;
                    cin >> response;
                    if (response == "y") {
                        subtractRollRims();
                        // TODO: set player state to not in jail and set jailTurns to 0 
                    } 
                } else {
                    cout << "You must roll doubles or pay $50 to get out of jail" << endl;
                    cout << "Do you want to roll or pay?[roll/pay]" << endl;
                    string response;
                    cin >> response;
                    if (response == "roll") {
                        vector<int> roll{Board.rollDice()};
                        if (roll[0] == roll[1]) {
                            
                        } else{


                        }
                    }
                }
            }
        } else if (cellName == "GoToTims") {
            
        } else if (cellName == "CoopFee") {
            subFunds(150);

        } else if (cellName == "Tuiton") {
            cout << "Do you want to pay $300 tuition or 10% of your total worth?[pay/10%]" << endl;
            string response;
            cin >> response;
            if (response == "pay") {
                subFunds(300);
            } else {
                subFunds(playerAssetsWorth() * 0.1);
            }

        } else if (cellName == "SLC") {
            int rollUpTheRim = rand() % 100;
            if (timsCupChance == 100) {
                rollRims++;
                //Ahmed implemented a get board global cup counter
                totalCups++;
                cout << "Congrats! You won a Roll Up the Rim cup" << endl;
            }

            int randNum = rand() % 24;
            


        } else if (cellName == "NeedlesHall") {
            int rollUpTheRim = rand() % 100;
            if (timsCupChance == 100) {
                rollRims++;
                //Ahmed implemented a get board global cup counter
                totalCups++;
                cout << "Congrats! You won a Roll Up the Rim cup" << endl;
            }

            int randNum = rand() % 18;
            
            if (randNum < 1) {
                subFunds(200);
            } else if (randNum < 3) {
                subFunds(100);
            } else if (randNum < 6) {
                subFunds(50);
            } else if (randNum <  12) {
                addFunds(25);
            } else if (randNum < 15) {
                addFunds(50);
            } else if (randNum < 17) {
                addFunds(100);
            } else if (randNum < 18) {
                addFunds(200);
            }
        }
    }
}

void Player::placePlayerHere(int newPosn, bool notifyCell = true) {
    playerPosn = newPosn;

    if (notifyCell) {
        state.playerPosn = playerPosn;
        state.type = StateType::Landed;
        state.cellName = "";
        state.newOwner = nullptr;
        notifyObservers();
    }
}

void Player::printAssets() {
    cout << "Name: " << playerName << endl;
    cout << "Character: " << pieceName << endl;
    cout << "Money: $" << money << endl;

    //Roll up rim cups
    if (rollRims > 0) {
        cout << "Number Roll up Rim Cups: " << rollRims << endl;
    }

    //properties owned
    for (auto &cell: ownedProperties) {
        cout << "Property: " << cell.getInfo()->cellName << " : $" << cell.getInfo()->price << endl;
    }
}

//Deals with bankrupt
int Player::playerAssetsWorth() {
    int totalAssets = 0;
    for (auto &cell: ownedProperties) {
        totalAssets += cell.getInfo().price;
    }
    totalAssets += money;
    return totalAssets;
}


// Function should be called when player wants to attempt to purchase the cell they are currenlty on.
// Should first evluate whether player should purchase or not, by seeing:
// 1. Player has enough money to purchase Cell
// 2. Cell is unowned
// After these are true, we need to deduct funds from player, addto list of properties, and increment counters.
void Player::attemptBuyProperty(std::shared_ptr<Subject<Info, State>> whoFrom) {
    Info *cellInfo = whoFrom->getInfo();
    
    // All the cases we shouldnt buy cell in
    // should probably put a descriptive error lollll
    if (cellInfo->posn != this->playerPosn) return;
    if (!cellInfo->ownable) return;
    if (cellInfo->ownedBy != nullptr) return;
    if (cellInfo->price > this->money) return;
    
    // Pay
    subFunds(cellInfo->price);

    // Add to prop vector
    ownedProperties.push_back(whoFrom);

    OwnableType otype = cellInfo->otype;

    // Increment counter based on property type
    if (otype == OwnableType::Gym) {
        numGyms++;
    } else if (otype == OwnableType::Residence) {
        numResidences++;
    } else if (otype == OwnableType::Academic) {
        // Update FacultyMap
        // god knows how this works bruh pls ask aiden again
        auto academic = dynamic_cast<AcademicBuildings*>(whoFrom.get());
        FacultyMap[std::get<1>(academic->academic_buildings[academic->getFacultyName(academic->getName(),academic->academic_buildings)])]++;
    }

    cout << "Successfully purchased cell!" << endl;
    // setting up and sending notification to all cells
    State newS = State();
    newS.type = StateType::Purchase;
    state = newS;
    notifyObservers();
}


/*
struct State {
    StateType type = StateType::Playing;
    int playerPosn = 0;
    std::string cellName = "";
    Player *newOwner = nullptr;
};
*/

// this function is called when:
// 1. Cell is owned by Player
// 2. Cell has already been notified that it is being sold, and responded with "success" reply.
void Player::sellPropertyTo(Player& new_owner, std::shared_ptr<Cell> c) {
    Info oprop = c->getInfo();

    if (oprop.ownable) {
        if (oprop->ownedBy == this) {
            // Pay
            addFunds(oprop.price);

            // Add to prop vector
            ownedProperties.push_back(c);

            // Increment counter based on property type
            if (oprop.otype == OwnableType::Gym) {
                numGyms++;
            } else if (oprop.otype == OwnableType::Residence) {
                numResidences++;
            } else if (oprop.otype == OwnableType::Academic) {

                // Update FacultyMap
                auto academic = dynamic_cast<AcademicBuildings*>(c.get());
                FacultyMap[std::get<1>(academic->academic_buildings[academic->getFacultyName(academic->getName(),academic->academic_buildings)])]++;
            }
       

}

void Player::sellPropertyTo(Player& new_owner, std::shared_ptr<Cell> c) {
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

void Player::addProperty(shared_ptr<Ownable> c) {
    ownedProperties.push_back(c);
}


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
        p.setJailTurns(0);
    }
}
