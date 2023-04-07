#include "textdisplay.h"
#include <iostream>
#include "board.h"
#include <fstream>
#include <string>

using namespace std;

class State;

void TextDisplay::updateDisplay(shared_ptr<Cell> cell, int r, int c) {
    
}


TextDisplay::TextDisplay(): {
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

void TextDisplay::notify(Subject<Info, State> &whoNotified) {

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