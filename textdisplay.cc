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



void TextDisplay::updateBoard(Cell *cell) {
    cout << "updateBoard: " << endl;;
    std::vector<std::vector<char>> theDisplay2;

    ifstream board1("board.txt");
    string line;
    while (getline(board1, line)) {
        vector <char> row;
        for (int i = 0; i < line.length(); i++) {
            row.emplace_back(line[i]);
        }
        theDisplay2.emplace_back(row);
    }

    for (int i = 0; i < board.getPlayerList().size(); i++) {
        int playerPosn = board.getPlayerList()[i]->getPlayerPosn();
        int playerI = board.getCell(playerPosn)->getI();
        int playerJ = board.getCell(playerPosn)->getJ();
        
        if ((playerPosn < 10) || (playerPosn > 20 && playerPosn < 30)) {
            theDisplay2[playerJ][playerI + i + 1] = board.getPlayerList()[i]->getPieceName();
        } else {
            theDisplay2[playerJ - 1][playerI + i + 1] = board.getPlayerList()[i]->getPieceName();
        }
    }

    for (int i = 0; i < board.getCellList().size(); i++) {
        int cellPosn = board.getCellList()[i]->getPosn();
        int cellI = board.getCell(cellPosn)->getI();
        int cellJ = board.getCell(cellPosn)->getJ();
        int improveLevel = board.getCell(cellPosn)->getImproveCount();
        for (int j = 0; j < improveLevel; j++) {
            theDisplay2[cellJ + j + 1][cellI + 3] = 'I';
        }
    }


    theDisplay = theDisplay2;
}

// void TextDisplay::updateImprovement(shared_ptr<Cell> cell) {
//     int cordI = cell->getI();
//     int cordJ = cell->getJ();
//     int posn = cell->getPosn();
//     int improveLevel = cell->getImproveCount();

//     std::vector<std::vector<char>> theDisplay2;
//     ifstream board1("board.txt");
//     string line;
//     while (getline(board1, line)) {
//         vector <char> row;
//         for (int i = 0; i < line.length(); i++) {
//             row.emplace_back(line[i]);
//         }
//         theDisplay2.emplace_back(row);
//     }

//     for (int i = 0; i < improveLevel; i++) {
//         theDisplay[cordI + i + 1][cordJ + 3] = 'I';
//     }

// }


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
    Cell *whoFromCell = nullptr;
    string name = whoFrom->getName();
    for (int i = 0; i < board.getCellList().size(); i++) {
        if (board.getCellList()[i]->getName() == name) {
            whoFromCell = board.getCellList()[i].get();
        }
    }
    int posn = whoFromCell->getPosn();
    int improveLevel = whoFromCell->getImproveCount();
    bool ownable = whoFromCell->getOwnable();
    Cell *cell = board.getCell(posn);
    // iteratre through players and find the player that is on the cell that notified

    updateBoard(cell);
    //updateImprovement(cell);
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
