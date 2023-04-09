#include "textdisplay.h"
#include <iostream>
#include "board.h"
#include <fstream>
#include <string>
#include <vector>
#include "state.h"
#include "cell.h"
#include "board.h"

using namespace std;



void TextDisplay::updatePlayerPosn(shared_ptr<Cell> cell) {
    int cordI = cell->getI();
    int cordJ = cell->getJ();
    int posn = cell->getPosn();
    int playersOnCell = 0;
    vector<char> players;
    for (int i = 0; i < board.getPlayerList().size(); i++) {
        if (board.getPlayerList()[i]->getPlayerPosn() == posn) {
            playersOnCell++;
            players.emplace_back(board.getPlayerList()[i]->getPieceName());
        }
    }
    for (int i = 0; i < playersOnCell; i++) {
        theDisplay[cordI + i + 1][cordJ] = players[i];
    }
}

void TextDisplay::updateImprovement(shared_ptr<Cell> cell) {
    int cordI = cell->getI();
    int cordJ = cell->getJ();
    int posn = cell->getPosn();
    int improveLevel = cell->getImproveCount();
    for (int i = 0; i < improveLevel; i++) {
        theDisplay[cordI + i + 1][cordJ + 3] = 'I';
    }

}


TextDisplay::TextDisplay(Board &board): board{board} {
    ifstream board1("board.txt");
    string line;
    while (getline(board1, line)) {
        vector <char> row;
        for (int i = 0; i < line.length(); i++) {
            row.emplace_back(line[i]);
        }
        theDisplay.emplace_back(row);
    }
}

void TextDisplay::notify(std::shared_ptr<Subject<Info, State>> whoFrom) {
    // Assume that only cells notify us
    Cell *whoFromCell = dynamic_cast<Cell*>(whoFrom.get());
    if (whoFromCell == nullptr) return;

    string name = whoFromCell->getName();
    int posn = whoFromCell->getPosn();
    int improveLevel = whoFromCell->getImproveCount();
    bool ownable = whoFromCell->getOwnable();
    shared_ptr<Cell> cell = board.getCell(posn);
    // iteratre through players and find the player that is on the cell that notified
    for (int i = 0; i < board.getPlayerList().size(); i++) {
        if (board.getPlayerList()[i]->getPlayerPosn() == posn) {
            updatePlayerPosn(cell);
        }
    }
    if (ownable && improveLevel > 0) {
        updateImprovement(cell);
    }
}



ostream &operator<<(ostream &out, const TextDisplay &td) {
    for (int i = 0; i < td.theDisplay.size(); i++) {
        for (int j = 0; j < td.theDisplay[i].size(); j++) {
            out << td.theDisplay[i][j];
        }
        out << endl;
    }
    return out;
}