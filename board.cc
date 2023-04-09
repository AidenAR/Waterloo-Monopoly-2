#include "board.h"
#include "nonownable.h"
#include "ownable.h"
#include "player.h"
#include "property.h"
#include <iostream>

class CollectOsap;
class GoToTims;
class Slc;
class Tuition;
class CoopFee;

using namespace std;

Board::~Board() {
    delete td;
}

char Board::pieceSymbol(string pieceName) {
    swicth (pieceName) {
        case "Goose":
            return 'G';
        case "GRT Bus":
            return 'B';
        case "Tim Hortons Donut":
            return 'D';
        case "Professor":
            return 'P';
        case "Student":
            return 'S';
        case "Money":
            return '$';
        case "Laptop":
            return 'L';
        case "Pink Tie":
            return 'T';
    }
}

bool Board::findinVector(vector<string> v, string s) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == s) {
            return true;
        }
    }
    return false;
}

void Board::initializeCells() {
    Cells.emplace_back(make_shared<CollectOsap>(this, "COLLECT OSAP", 0, 80, 54));
    Cells.emplace_back(make_shared<Property>(this, "AL", 1, 72, 54));
    Cells.emplace_back(make_shared<Slc>(this, "SLC", 2, 64, 54));
    Cells.emplace_back(make_shared<Property>(this, "ML", 3, 56, 54));
    Cells.emplace_back(make_shared<Tuition>(this, "TUITION", 4, 48, 54));
    Cells.emplace_back(make_shared<Residences>(this, "MKV", 5, 40, 54));
    Cells.emplace_back(make_shared<Property>(this, "ECH", 6, 32, 54));
    Cells.emplace_back(make_shared<NeedlesHall>(this, "NEEDLES HALL", 7, 24, 54));
    Cells.emplace_back(make_shared<Property>(this, "PAS", 8, 16, 54));
    Cells.emplace_back(make_shared<Property>(this, "HH", 9, 8, 54));
    Cells.emplace_back(make_shared<DCTimsLine>(this, "DC TIMS LINE", 10, 0, 54));
    Cells.emplace_back(make_shared<Property>(this, "RCH", 11, 0, 51));
    Cells.emplace_back(make_shared<gyms>(this, "PAC", 12, 0, 46));
    Cells.emplace_back(make_shared<Property>(this, "DWE", 13, 0, 41));
    Cells.emplace_back(make_shared<Property>(this, "CPH", 14, 0, 36));
    Cells.emplace_back(make_shared<Residences>(this, "UWP", 15, 0, 31));
    Cells.emplace_back(make_shared<Property>(this, "LHI", 16, 0, 26));
    Cells.emplace_back(make_shared<Slc>(this, "SLC", 17, 0, 21));
    Cells.emplace_back(make_shared<Property>(this, "BMH", 18, 0, 16));
    Cells.emplace_back(make_shared<Property>(this, "OPT", 19, 0, 11));
    Cells.emplace_back(make_shared<Goose>(this, "GOOSE NESTING", 20, 0, 4));
    Cells.emplace_back(make_shared<Property>(this, "EV1", 21, 8, 0));
    Cells.emplace_back(make_shared<NeedlesHall>(this, "NEEDLES HALL", 22, 16, 4));
    Cells.emplace_back(make_shared<Property>(this, "EV2", 23, 24, 4));
    Cells.emplace_back(make_shared<Property>(this, "EV3", 24, 32, 4));
    Cells.emplace_back(make_shared<Residences>(this, "V1", 25, 40, 4));
    Cells.emplace_back(make_shared<Property>(this, "PHYS", 26, 48, 4));
    Cells.emplace_back(make_shared<Property>(this, "B1", 27, 56, 4));
    Cells.emplace_back(make_shared<gyms>(this, "CIF", 28, 64, 4));
    Cells.emplace_back(make_shared<Property>(this, "B2", 29, 72, 4));
    Cells.emplace_back(make_shared<GoToTims>(this, "GO TO TIMS", 30, 80, 4));
    Cells.emplace_back(make_shared<Property>(this, "EIT", 31, 80, 11));
    Cells.emplace_back(make_shared<Property>(this, "ESC", 32, 80, 16));
    Cells.emplace_back(make_shared<Slc>(this, "SLC", 33, 80, 21));
    Cells.emplace_back(make_shared<Property>(this, "C2", 34, 80, 26));
    Cells.emplace_back(make_shared<Residences>(this, "REV", 35, 80, 31));
    Cells.emplace_back(make_shared<NeedlesHall>(this, "NEEDLES HALL", 36, 80, 36));
    Cells.emplace_back(make_shared<Property>(this, "MC", 37, 80, 41));
    Cells.emplace_back(make_shared<CoopFee>(this, "COOP FEE", 38, 80, 46));
    Cells.emplace_back(make_shared<Property>(this, "DC", 39, 80, 51));
    for int(int i = 0; i < 39; i++) {
        Cells[i]->attach(td);
    }
}

void Board::init() {
    td = make_shared<TextDisplay>(*this);
    initializeCells();
    int numPlayers;
    std::vector<std::string> chosenPieces;
    cout << "How many players are joining the game?" << endl;
    cin >> numPlayers;
    while (numPlayers > 8 || numPlayers < 2) {
        cout << "Please enter a number between 2 and 8." << endl;
        cin >> numPlayers;
    }
    cout << "Now it's time to choose your pieces!" << endl;
    cout << "Please select a piece from the following list:" << endl;
    for (int i = 0; i < pieceList.size(); i++) {
        cout << pieceList[i] << endl;
    }
    for (int i = 0; i < numPlayers; i++) {
        string name;
        string piece;
        cout << "What is the name of player" << i << "?" << endl;
        cin >> name;
        cout << "What is the piece of player" << i << "?" << endl;
        cin >> piece;
        while (findinVector(pieceList, piece)) {
            cout << "Please enter a valid piece!" << endl;
            cin >> piece;
        }
        while(findinVector(chosenPieces, piece)) {
            cout << piece << " has already been choesen, please select a different piece!" << endl;
        }
        shared_ptr<Player> p = make_shared<Player>(name, pieceSymbol(piece), 1500, 0, 0);
        playerList.emplace_back(p);
    }
}

vector<int> Board::rollDice() {
    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;
    vector<int> dice;
    dice.emplace_back(dice1);
    dice.emplace_back(dice2);
    return dice;
}

std::vector<std::shared_ptr<Player>> Board::getPlayerList() {
    return playerList;
}

std::shared_ptr<Cell> Board::getCell(int i) {
    return Cells[i];
}

Player *currentPlayer() {
    // TODO
}

void Board::saveGame(std::string f) {
    ofstream file;
    file.open(f);
    file << playerList.size() << endl;
    for (int i = 0; i < playerList.size(); i++) {
        file << playerList[i]->getPlayerName() << " " << playerList[i]->getPieceName() << " " << playerList[i]->getMoney() << " " << playerList[i]->getPlayerPos() << " " << playerList[i]->getRollRims() << endl;
        // add if player in jail or not
        if (playerList[i]->timsJail) {
            file << "true" << playerList[i]->jailTurns << endl;
        } else {
            file << "false" << endl;
        }
        file << playerList[i]->ownedProperties.size() << endl;
        for (int j = 0; j < playerList[i]->ownedProperties.size(); j++) {
            file << playerList[i]->ownedProperties[j]->getName() << " " << playerList[i]->ownedProperties[j]->getImproveLevel() << endl;
        }
    }
    file.close();
    cout << "Game saved!" << endl;
}

void Board::loadGame(std::string f) {
    ifstream saved(f);
    string line;
    getline(saved, line);
    int numPlayers = stoi(line);
    for (int i = 0; i < numPlayers; i++) {
        getline(saved, line);
        istringstream iss(line);
        string name, piece;
        int money, playerPosn, rollRims;
        iss >> name >> piece >> money >> playerPosn >> rollRims;
        shared_ptr<Player> p = make_shared<Player>(name, pieceSymbol(piece), money, playerPosn, rollRims);
        playerList.emplace_back(p);
        getline(saved, line);
        istringstream iss2(line);
        string inJail;
        iss2 >> inJail;
        if (inJail == "true") {
            p->timsJail = true;
            iss2 >> p->jailTurns;
        } else {
            p->timsJail = false;
        }
        getline(saved, line);
        istringstream iss3(line);
        int numProperties;
        iss3 >> numProperties;
        for (int j = 0; j < numProperties; j++) {
            getline(saved, line);
            istringstream iss4(line);
            string propertyName;
            int improveLevel;
            iss4 >> propertyName >> improveLevel;
            for (int k = 0; k < Cells.size(); k++) {
                if (Cells[k]->getName() == propertyName) {
                    p->ownedProperties.emplace_back(Cells[k]);
                    Cells[k].getInfo().ownedBy = p;
                    Cells[k].getInfo().improveLevel = improveLevel;
                    p->addProperty(Cells[k]);
                }
            }
        }
    }
}

ostream Board::&operator<<(ostream &out, const Grid &g) {
    out << *(g.td);
    return out;
}

bool Board::isGameOver() {
    if (playerList.size() == 1) {
        return true;
    }
}
