//
// Created by aiden on 03/04/2023.
//

#include "player.h"
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "board.h"
#include <unordered_map>
#include "state.h"
#include "board.h"
#include <tuple>
#include <memory>
#include "cell.h"
#include "ownable.h"

using namespace std;

Player::Player(Board *board, string playerName, char pieceName, int money, int rollRims, int playerPosn): board{board},
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


State *Player::getState() {
    return &state;
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

    if (add_cup == 1 && board->getTotalCups() < 4 && getRollRims() < 4) {
        rollRims++;
        //Ahmed implemented a get board global cup counter
        board->addToTotalCups();
        cout << "Congrats! You won a Roll Up the Rim cup" << endl;
    }
}

void Player::subtractRollRims() {
    rollRims = rollRims > 0 ?  rollRims-- : 0;
    
    if (board->getTotalCups() > 0) {
        board->removeFromTotalCups();
    }
    jailTurns = 0;
    timsJail = false;
    jailRolls.clear();
    //rollMove();
}

// Takes in new position newPosn we place the player in that position.
// notifyCell controls whether the cell upon which we just placed the Player should be notified of this.
// Eg, during instantiation when we place each player, dont want to notify cell.
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


// moveForward() will move player forward by one; intention is, if we need to move 5, we call moveForward() 5 times.
// This will notify all observers that Player is moving forward by 1 (Move notif). 
// On the 5th moving, specify that player has landed on that spot with landed=true (Landed notif).
void Player::moveForward(bool landed = false) {
    if (this->timsJail) return;

    playerPosn++;

    state.cellName = "";
    state.type = landed ? StateType::Landed : StateType::Move;
    state.playerPosn = playerPosn;

    cout << "boutta send landed notif lfg" << endl;

    this->notifyObservers();
}

void Player::subFunds(int num) {
    money -= num;
    //TODO: should do bankruptin here if money<0
}

void  Player::addFunds(int num) {
    money += num;
}

shared_ptr<Cell> Player::findCell(shared_ptr<Cell> cell) {
    for (auto &c : ownedProperties) {
        if (c.get() == cell.get()) {
            return c;
        }
    }
    return nullptr;
}

// As this is a Player, we will only be notified by Cells, so Cells contain data with their Info attribute; use Info accessors.
// Do NOT call State accessors here.
// The only cells which will be notifying us are those who want the player to do smth (ie, pay tuiton)
void Player::notify(Subject &whoFrom) {
    // should do nothing if it isnt this Players turn

    Cell *whoFromCell = dynamic_cast<Cell*>(&whoFrom);
    if (whoFromCell == nullptr) return;

    this->responseCell = std::make_shared<Cell>(*whoFromCell);

    string cellName = whoFromCell->getName();
    
    cout << "You landed on:" << endl;
    cout << cellName << endl;

    // for convenience:
    // vector<string> academicBuildings = {"AL","ML","ECH","PAS","HH","RCH","DWE","CPH""LHI","BMH","OPT","EV1","EV2","EV3","PHYS","B1","B2","EIT","ESC","C2","MC","DC"};
    // vector<string> residences = {"MKV","UWP","V1","REV"};
    // vector<string> gyms = {"PAC","CIF"};

    if (whoFromCell->getOwnable()) {
        // Ownable

        // when should ownable cells even be notifyin??
        // cuz tuition is hanlded by the cell itself.
        // when we land on a cell and send Landed notif, wtf happens?
        // if we own cell, then nothing.
        // if other own cell, charge tuition (handled cell side!!).
        // else, nobody own. then:
        //      player can: buy or auction.
        //      so when cell sees its unowned and been lande upon, cell notifies observers.
        //      our cell should recognize its been notified by an unowned cell, and should in response:
        //          ask player to purchase, or run auction.

        // however if player wants to like add improvements, then we send another request, but thats not handled here.

        if (whoFromCell->getOwnedBy() == nullptr) {
            cout << "Cell owned by nobody, would you like to purchase for: " << whoFromCell->getPrice() << "\n[y/n]" << endl;
            cout << "Note, not buying will result in cell being auctioned." << endl;
            
            string response;
            cin >> response;

            while (true) {
                if (response == "y") {
                    attemptBuyProperty(whoFromCell);
                    break;
                } else if (response == "n") {
                    cout << "Auctioning time!" << endl;
                    // TODO:
                    // AUCTION DAT!!!
                    break;
                } else {
                    cout << "please enter again!!" << endl;
                }
            }
        }
        
    } else {
        // Non-ownable
        if (cellName == "OCollectOsapSAP") {
            addFunds(200);
        } else if (cellName == "DcTimsLine") {
            if (getTimsJail()) {
                if (getRollRims() > 0) {
                    cout << "Do you want to use a roll up the rim cup to get out of jail?[y/n]" << endl;
                    string response;
                    cin >> response;
                    if (response == "y") {
                        subtractRollRims();
                        // TODO: set player state to not in jail and set jailTurns to 0 
                        freePlayerFromTimsJail();
                    } 
                } else if (getJailTurns() == 3) {
                    cout << "You have been in jail for 3 turns, you must pay $50 to get out" << endl;
                    subFunds(50);
                    //TODO: if player doesnt have funds for it, then auctioning time!
                    subtractRollRims();
                } else {
                    cout << "You must roll doubles or pay $50 to get out of jail" << endl;
                    cout << "Do you want to roll or pay?[roll/pay]" << endl;
                    string response;
                    cin >> response;

                    while (true) {
                        if (response == "roll") {
                            vector<int> roll{Board().rollDice()};
                            if (roll[0] == roll[1]) {
                                freePlayerFromTimsJail();
                            } else{
                                cout << "Unfortunatley didnt roll doubles, sstaying in Jail );";
                            }
                            break;
                        } else if (response == "pay") {
                            subFunds(50);
                            break;
                        } else {
                            cout << "Please enter valid response" << endl;
                        }
                    }

                }
            }
        } else if (cellName == "GoToTims") {
            // We have no reason to be notified by this cell. we do nothing.
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
            addRollRims();

            int randNum = rand() % 24;
            
            // lmao these probabilities are fs way off but idc tbh
            if (randNum < 1) {
                placePlayerHere(10); // DC tims line
                //TODO: put player in jail
            } else if (randNum < 5) {
                placePlayerHere(whoFromCell->getPosn() - 2);
                //
            } else if (randNum < 9) {
                placePlayerHere(whoFromCell->getPosn() - 1);
                //
            } else if (randNum < 13) {
                placePlayerHere(whoFromCell->getPosn() + 2);
                //
            } else if (randNum < 17) {
                placePlayerHere(whoFromCell->getPosn() + 3);
                //
            } else if (randNum < 20) {
                placePlayerHere(whoFromCell->getPosn() - 2);
                //
            } else if (randNum < 23) {
                placePlayerHere(whoFromCell->getPosn() - 2);
                //
            } else if (randNum < 24) {
                placePlayerHere(0);
                //
            } 


        } else if (cellName == "NeedlesHall") {
            addRollRims();
            

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

void Player::freePlayerFromTimsJail() {
    timsJail = false;
    jailTurns = 0;
    jailRolls.clear();
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
        cout << "Property: " << cell->getName() << " : $" << cell->getPrice() << endl;
    }
}

//Deals with bankrupt
int Player::playerAssetsWorth() {
    int totalAssets = 0;
    for (auto &cell: ownedProperties) {
        totalAssets += cell->getPrice();
    }
    totalAssets += money;
    return totalAssets;
}


void Player::attemptAddImprovement(string cellName) {
    state.type = StateType::AddImprovement;
    state.cellName = cellName;
    state.newOwner = nullptr;

    notifyObservers();
}

void Player::attemptSellImprovement(string cellName) {
    state.type = StateType::SellImprovement;
    state.cellName = cellName;
    state.newOwner = nullptr;

    notifyObservers();
}

void Player::attemptMortgage(string cellname) {
    state.type = StateType::Mortgage;
    state.cellName = cellname;
    state.newOwner = nullptr;

    notifyObservers();
}

void Player::attemptUnmortgage(string cellname) {
    state.type = StateType::Unmortgage;
    state.cellName = cellname;
    state.newOwner = nullptr;

    notifyObservers();
}


// Function should be called when player wants to attempt to purchase the cell they are currenlty on.
// Should first evluate whether player should purchase or not, by seeing:
// 1. Player has enough money to purchase Cell
// 2. Cell is unowned
// After these are true, we need to deduct funds from player, addto list of properties, and increment counters.
void Player::attemptBuyProperty(Cell *whoFrom) {
    
    // All the cases we shouldnt buy cell in
    // should probably put a descriptive error lollll
    if (whoFrom->getPosn() != this->playerPosn) return;
    if (!whoFrom->getOwnable()) return;
    if (whoFrom->getOwnedBy() != nullptr) return;
    if (whoFrom->getPrice() > this->money) return;
    
    // Pay
    subFunds(whoFrom->getPrice());

    // Add to prop vector
    ownedProperties.emplace_back(*whoFrom);

    OwnableType otype = whoFrom->getOtype();

    // Increment counter based on property type
    if (otype == OwnableType::Gym) {
        numGyms++;
    } else if (otype == OwnableType::Residence) {
        numResidences++;
    } else if (otype == OwnableType::Academic) {
        // Update FacultyMap
        // god knows how this works bruh pls ask aiden again
        // auto academic = dynamic_cast<AcademicBuildings*>(whoFrom.get());
        // FacultyMap[std::get<1>(academic->academic_buildings[academic->getFacultyName(academic->getInfo()->cellName)])]++;
    }

    cout << "Successfully purchased cell!" << endl;
    // setting up and sending notification to all cells; ie, attempting the purchase
    state.type = StateType::Purchase;
    state.newOwner = nullptr;
    state.cellName = "";

    notifyObservers();
}

// a quick helper function for attemptTrade()
bool isNum(string str) {
    int len = str.length();
    for (int i = 0; i < len; i++) {
        if(!isdigit(str[i])) return false;
    }
    return true;
}

// Attempt trade from current player to name, where we give smth and recieve smth.
// Requirements:
// - we are assured that tradeTo is the player to whom we will be trading to (main function problem).
void Player::attemptTrade(Player *tradeTo, std::string give, std::string recieve) {
    // Three cases:
    // give money, recieve property
    int giveInt = stoi(give);
    if (isNum(give)) {
        
        if (giveInt > this->money) {
            // means we dont have the funds for this trade!
            cout << "You do not have enough money for trade );" << endl;
            return;
        }

        if (isNum(recieve)) {
            cout << "Invalid trade!! Cant trade money for money lol." << endl;
            return;
        } else {
            // I am paying money for other guys property

            tradeTo->sellPropertyTo(recieve, this, giveInt);
        }
    } else {
        if (isNum(recieve)) {
            // I am selling my property to other guy for money
            
            int recieveInt = stoi(recieve);
            if (recieveInt > tradeTo->money) {
                cout << "Other player does not have enough money for trade );" << endl;
                return;
            }

            sellPropertyTo(give, tradeTo, recieveInt);
        } else {
            // I am trading property with the other guy
            sellPropertyTo(give, tradeTo, 0);
            tradeTo->sellPropertyTo(recieve, this, giveInt);
        }
    }
}

// Helpful for anything around selling properties. 
// If newOwner is not provided, means we arent selling it to anybody
// newOwner represents person property is sold to.
// c is the property we want to sell.
// salePrice represents an overridden sale price, if its not provided then means property sold to us for its normal price.
// else, we are sold the property for the amount salePrice. 
// Requirements:
// None
void Player::sellPropertyTo(string cellName, Player *newOwner, int salePrice) {
    // Before selling property, lets verify funds.

    if (salePrice > newOwner->money) {
        cout << "Not enough money to trade" << endl;
    }

    // Setting up State
    state.type = StateType::SellTo;
    state.cellName = cellName;
    state.newOwner = newOwner; // argh casting issues!!1!1!

    responseCell = nullptr;
    
    // We attempt to do this trade
    notifyObservers();
    
    // After notifyObservers() finishes, responseCell should update with intended cell
    // (as it is the only cell which should respond)

    if (!responseCell->getSuccesful()) {
        cout << "Unsuccessful trade );" << endl;
        return;
    }

    // Since trade was successful on Cell side and all its attributes are updated, lets update our Players. 

    if (salePrice == -1) {
        salePrice = responseCell->getPrice();
    }

    // Pay
    addFunds(salePrice);
    newOwner->subFunds(salePrice);

    // Add to newOwner property vector
    std::vector<std::shared_ptr<Cell>> traderProps = newOwner->getOwnedProperties();
    traderProps.push_back(responseCell);
    
    // Remove from our property vector
    auto it = findCell(responseCell);
    ownedProperties.erase(it);

    // Increment counter based on property type
    if (responseCell->getOtype() == OwnableType::Gym) {
        numGyms--;
        newOwner->numGyms++;
    } else if (responseCell->getOtype() == OwnableType::Residence) {
        numResidences--;
        newOwner->numResidences++;
    } else if (responseCell->getOtype() == OwnableType::Academic) {
        // Update FacultyMap
        auto academic = dynamic_pointer_cast<Ownable>(responseCell);
        if (academic == nullptr) return;
        string facultyName = academic->getFacultyName(academic->getName());
        
        // Increment the faculty count for the new owner
        newOwner->FacultyMap[facultyName].first++;

        // Decrement the faculty count for the previous owner
        if (FacultyMap.find(facultyName) != FacultyMap.end()) {
            FacultyMap[facultyName].first--;
        }
    }
}




//Handles jail rolls as well as jail turns
void Player::setJailTurns(int j) {
    jailTurns = j;
}

void Player::addProperty(shared_ptr<Ownable> c) {
    ownedProperties.emplace_back(c);
}

void Player::setTimsJail(bool j) {
    timsJail = j;
}

void Player::TimsJailCell(Player& p) {
    // Check if the player is currently in jail
    if (p.getTimsJail()) {
        // Check if it is the player's third turn in jail
        if (p.getJailTurns() == 3) {
            // Player must pay $50 or use a Roll Up the Rim cup to get out of jail
            if (p.getRollRims() > 0) {
                // Use Roll Up the Rim cup to get out of jail
                p.subtractRollRims();
                p.setTimsJail(false);
            } else if (p.getMoney() >= 50) {
                // Pay $50 to get out of jail
                p.subFunds(50);
                p.setTimsJail(false);
            } else {
                // Player doesn't have enough money to get out of jail
                p.setTimsJail(true);
            }
        } else {
            //in main or board???
            // Player must roll the dice to try to get doubles
            int diceRoll1 = board->rollDice()[0];
            int diceRoll2 = board->rollDice()[1];
            if (diceRoll1 == diceRoll2) {
                // Player rolled doubles and gets out of jail
                p.setJailTurns(0);
                p.setTimsJail(false);
            } else {
                // Player did not roll doubles
                p.setJailTurns(p.getJailTurns() + 1);
                p.setTimsJail(true);
            }
        }
    } else {
        // Player is not in jail
        p.setTimsJail(false);
        p.setJailTurns(0);
    }
}


void Player::partMonopoly() {
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