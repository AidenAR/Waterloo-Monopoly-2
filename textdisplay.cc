#include "textdisplay.h"
#include <iostream>
#include "board.h"
#include <fstream>
#include <string>
#include <vector>
#include "state.h"
#include "cell.h"
#include "board.h"
#include "player.h"
#include "subject.h"
#include <memory>

using namespace std;



void TextDisplay::updatePlayerPosn(Cell *cell) {
    cout << "updatePlayerPosn" << endl;
    int cordI = cell->getI();
    int cordJ = cell->getJ();
    int posn = cell->getPosn();
    int playersOnCell = 0;
    Cell *lastCellOn;
    vector<Player *> players;

    // for (int i = 0; i < board.getCellList().size(); i++) {
    //     if (board.getCellList()[i]->getPosn() != posn) {
    //         for (int j = 0; j < board.getPlayerList().size(); j++) {
    //             if (board.getPlayerList()[j]->getPlayerPosn() == posn) {
    //                 theDisplay[board.getCellList()[i]->getJ()][board.getCellList()[i]->getI() + 1] = space;
    //             }
    //         }
    //     }
    // }

    for (int i = 0; i < board.getPlayerList().size(); i++) {
        if (board.getPlayerList()[i]->getPlayerPosn() == posn) {
            playersOnCell++;
            cout << "entered if statement in updatePlayerPosn for updating display" << endl;
            cout << "player name: " << board.getPlayerList()[i]->getPieceName() << endl;
            players.emplace_back(board.getPlayerList()[i]);
        }
    }
    for (int i = 0; i < playersOnCell; i++) {
        cout << "entered for loop in updatePlayerPosn for updating display" << endl;
        cout << "cordI + i + 1 = " << cordI + i + 1 << endl;
        cout << "cordJ = " << cordJ << endl;
        cout << "i = " << i << endl;
        theDisplay[cordJ][cordI + i + 1] = players[i]->getPieceName();
    
        lastCellOn = board.getCellList()[players[i]->getLastPosn()].get();

        for (int i=lastCellOn->getI(); i< lastCellOn->getI() + 7; i++) {
            if (theDisplay[lastCellOn->getJ()][lastCellOn->getI() + i + 1] = players[i]->getPieceName()) {
                theDisplay[lastCellOn->getJ()][lastCellOn->getI() + i + 1] = space;
                break;
            }
        }
        ;
    }





}

void TextDisplay::updateImprovement(Cell *cell) {
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

void TextDisplay::notify(Subject *whoFrom) {
    cout << "textdisplay notified" << endl;
    // Assume that only cells notify us
    Cell *whoFromCell = dynamic_cast<Cell *>(whoFrom);
    string name = whoFromCell->getName();
    
    int posn = whoFromCell->getPosn();
    int improveLevel = whoFromCell->getImproveCount();
    bool ownable = whoFromCell->getOwnable();
    
    // iteratre through players and find the player that is on the cell that notified
    for (int i = 0; i < board.getPlayerList().size(); i++) {
        if (board.getPlayerList()[i]->getPlayerPosn() == posn) {
            updatePlayerPosn(whoFromCell);
        }
    }
    if (ownable && improveLevel > 0) {
        updateImprovement(whoFromCell);
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