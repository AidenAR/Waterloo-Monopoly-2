//
// Created by aiden on 03/04/2023.
//

#include "player.h"
#include <string>
#include <algorithm>

using namespace std;
#include <cstdlib>
#include <iostream>


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


State *Player::getState() const {
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
    if (this->timsJail) return;

    playerPosn++;

    state.type = landed ? StateType::Landed : StateType::Move;
    state.playerPosn = playerPosn;

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
// The only cells which will be notifying us are those who want the player to do smth (ie, pay tuiton)
void Player::notify(std::shared_ptr<Subject<Info, State>> whoFrom) {
    // should do nothing if it isnt this Players turn

    Info *info = whoFrom->getInfo();
    this->responseCell = whoFrom;

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
                cout << "Auctioning time!" << endl;
                // TODO:
                // AUCTION DAT!!!
            }
        } else if (info->ownedBy == this) {
            cout << "Cell owned by you!" << endl;
            //TODO?? lol not rly sure if anything neesd to be done here
        } else {
            cout << "Cell not owned by you... gotta pay up!" << endl;

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
            money += 200; //lol idk
        } else if (cellName == "DcTimsLine") {

        } else if (cellName == "GoToTims") {

        } else if (cellName == "CoopFee") {

        } else if (cellName == "Tuiton") {

        } else if (cellName == "SLC") {

        } else if (cellName == "NeedlesHall") {

        }
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
void Player::attemptBuyProperty(std::shared_ptr<Cell> whoFrom) {
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
    // setting up and sending notification to all cells; ie, attempting the purchase
    State newS = State();
    newS.type = StateType::Purchase;
    state = newS;
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
void Player::attemptTrade(std::shared_ptr<Player> tradeTo, std::string give, std::string recieve) {
    // Three cases:
    // give money, recieve property
    if (isNum(give)) {
        int giveInt = stoi(give);
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

            tradeTo->sellPropertyTo(this, recieve, giveInt);
        }
    } else {
        if (isNum(recieve)) {
            // I am selling my property to other guy for money
            
            int recieveInt = stoi(recieve);
            if (recieveInt > tradeTo->money) {
                cout << "Other player does not have enough money for trade );" << endl;
                return;
            }

            sellPropertyTo(tradeTo, give, recieveInt);
        } else {
            // I am trading property with the other guy
            sellPropertyTo(tradeTo, give, 0);
            tradeTo->sellPropertyTo(this, recieve, 0);
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
void Player::sellPropertyTo(std::shared_ptr<Player> newOwner = nullptr, string cellName, int salePrice = -1) {
    // Before selling property, lets verify funds.

    if (salePrice > newOwner->money) {
        cout << "Not enough money to trade" << endl;
    }

    // Setting up State
    state.type = StateType::SellTo;
    state.cellName = cellName;
    state.newOwner = newOwner; // argh casting issues!!1!1!
    
    // We attempt to do this trade
    notifyObservers();
    
    // After notifyObservers() finishes, responseCell should update with intended cell
    // (as it is the only cell which should respond)
    Info *oprop = responseCell->getInfo();

    if (!oprop->wasSuccesful) {
        cout << "Unsuccessful trade );" << endl;
        return;
    }

    // Since trade was successful on Cell side and all its attributes are updated, lets update our Players. 

    if (salePrice == -1) {
        salePrice = oprop->price;
    }

    // Pay
    addFunds(salePrice);
    newOwner->subFunds(salePrice);

    // Add to newOwner property vector
    std::vector<std::shared_ptr<Cell>> traderProps = newOwner->getOwnedProperties();
    traderProps.push_back(responseCell);
    
    // Remove from our property vector
    auto it = std::find(ownedProperties.begin(), ownedProperties.end(), responseCell);
    if (it != ownedProperties.end()) {
        ownedProperties.erase(it);
    }

    // Increment counter based on property type
    if (oprop->otype == OwnableType::Gym) {
        numGyms--;
        newOwner->numGyms++;
    } else if (oprop->otype == OwnableType::Residence) {
        numResidences--;
        newOwner->numResidences++;
    } else if (oprop->otype == OwnableType::Academic) {

        // Update FacultyMap
        auto academic = dynamic_cast<AcademicBuildings*>(responseCell.get());

        newOwner->FacultyMap[std::get<1>(academic->academic_buildings[academic->getFacultyName(academic->getName(),academic->academic_buildings)])]++;
        FacultyMap[std::get<1>(academic->academic_buildings[academic->getFacultyName(academic->getName(),academic->academic_buildings)])]--;
    }

}




//Handles jail rolls as well as jail turns
void Player::setJailTurns(int j) {
    jailTurns = j;
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

