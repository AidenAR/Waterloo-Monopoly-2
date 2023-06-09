#include "cell.h"
#include "board.h"
#include <string>

using namespace std;


Cell::Cell(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price) : 
    board{board}, name{name}, posn{posn}, i{i}, j{j}, ownable{ownable}, otype{otype}, price{price} {}

Player *Cell::getOwnedBy() {
    return ownedBy;
}

OwnableType Cell::getOtype() {
    return otype;
}

void Cell::setOwnedBy(Player *ownedBy) {
    this->ownedBy = ownedBy;
}

string Cell::getName() {
    return name;
}

int Cell::getPosn() {
    return posn;
}

void Cell::event(Player* p){}


int Cell::getI() {
    return i;
}
int Cell::getJ() {
    return j;
}

bool Cell::getSuccesful() {
    return wasSuccesful;
}
void Cell::setSuccesful(bool wasSuccesful) {
    this->wasSuccesful = wasSuccesful;
}
bool Cell::getOwnable() {
    return ownable;
}

int Cell::getImproveCount() {
    return improveCount;
}
void Cell::setImproveCount(int newImprove) {
    improveCount = newImprove;
}

int Cell::getPrice() {
    return price;
}
bool Cell::getMortgaged() {
    return isMortgaged;
}
void Cell::setMortgaged(bool isMortgaged) {
    this->isMortgaged = isMortgaged;
}
