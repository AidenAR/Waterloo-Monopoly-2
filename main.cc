#include "board.h"
#include "cell.h"
#include "player.h"
#include <iostream>
#include <vector>
#include "ownable.h"
#include "nonownable.h"

using namespace std;


//Note:
// if argc != 1 we get issues (shit!)


int main(int argc, char *argv[]) {

    Board b;
    bool testing = false;
    string loadfile = "";

    for (int i = 0; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-testing") {
            testing = true;
        } else if (arg == "-load") {
            if (argc == ++i) {
                loadfile = argv[i];
            }
        } else {
            cout << "invalid arguments" << endl;
        }

    }
    cout << "Welcome to the game!" << endl;
    if (argc == 1) {
        b.init();
        cout << b;

        int currentPlayer = 0;
        vector<shared_ptr<Player>> players = b.getPlayerList();
        while(!b.isGameOver()) {
            cout << "enter help for a list of commands" << endl;
            string cmd;
            Player *p = players[currentPlayer].get();
            cin >> cmd;
            if (cmd == "help") {
                cout << "roll: roll the dice" << endl;
                cout << "next (used if the player cannot roll): give control to the next player." << endl;
                cout << "trade <name> <give> <receive>: offers a trade to name with the current player offering give and requesting receive, where give and receive are either amounts of money or a property name. Responses are accept and reject." << endl;
                cout << "improve <property> buy/sell: attempts to buy or sell an improvement for property." << endl;
                cout << "mortgage <property>: attempts to mortgage property." << endl;
                cout << "unmortgage <property>: attempts to unmortgage property." << endl;
                cout << "assets: prints out a list of all the assets of the current player." << endl;
                cout << "all: displays the assets of every player. For verifying the correctness of your transactions. Does not work if a player is deciding how to pay Tuition." << endl;
                cout << "save <filename>: saves the current state of the game to filename." << endl;
            } else if (cmd == "roll") {
                vector <int> dice = b.rollDice();
                cout << "You rolled a " << dice[0] << " and a " << dice[1] << endl;
                int diceRollCount = 1;
                int diceTotal = dice[0] + dice[1];
                while (dice[0] == dice[1]) {
                    diceRollCount++;
                    if (diceRollCount == 3) {
                        cout << "You rolled three doubles in a row, you are sent to DC Tims Line." << endl;
                        p->setPlayerPosn(10);

                        p->setTimsJail(true);
                        break;
                    }
                    cout << "You rolled doubles, you get to roll again!" << endl;
                    dice = b.rollDice();
                    diceTotal += dice[0] + dice[1];
                    cout << "You rolled a " << dice[0] << " and a " << dice[1] << endl;
                }
                int newPosn = (p->getPlayerPosn() + diceTotal) % 40;
                p->setPlayerPosn(newPosn);
                cout << "You are now on " << b.getCell(newPosn)->getName() << endl;
                b.getCell(newPosn)->notifyObservers();
                b.getCell(newPosn)->event(p);

                cout << b;
                
            } else if (cmd == "next") {
                currentPlayer++;
                p = players[currentPlayer % players.size()].get();
                continue;
            } else if (cmd == "trade") {
                string name, give, receive;
                cin >> name >> give >> receive;
                cout << "You offered to trade " << give << " for " << receive << " with " << name << endl;
                cout << name << "enter accept/reject" << endl;
                string response;
                cin >> response;
                while (response != "accept" && response != "reject") {
                    cout << "Invalid response, trade rejected!" << endl;
                    cout << name << "enter accept/reject" << endl;
                    cin >> response;
                }
                if (response == "accept") {
                    cout << "Trade accepted!" << endl;
                    Player *tradeTo = nullptr;
                    for (int i = 0; i < players.size(); i++) {
                        if (players[i]->getName() == name) {
                            tradeTo = players[i].get();
                        }
                    }
                    //p->attemptTrade(tradeTo.get(), give, receive);
                } else if (response == "reject") {
                    cout << "Trade rejected!" << endl;
                    continue;
                }
            } else if (cmd == "improve") {
                string property, buySell;
                cin >> property >> buySell;
                Ownable *c = nullptr;
                std::vector<Cell *> ownedProperties = p->getOwnedProperties();
                for (int i = 0; i < ownedProperties.size(); i++) {
                    if (ownedProperties[i]->getName() == property) {
                        c = dynamic_cast<Ownable*>(ownedProperties[i]);
                    }
                }
                if (c == nullptr) {
                    cout << "You do not own this property, you cannot improve it." << endl;
                } else {
                    while (buySell != "buy" && buySell != "sell") {
                        cout << "Invalid command, please enter a valid command." << endl;
                        cin >> buySell;
                    }
                    if (buySell == "buy") {
                        c->buyImprovement();
                    } else if (buySell == "sell") {
                        c->sellImprovement();
                    }
                }
            } else if (cmd == "mortgage") {
                string property;
                cin >> property;
                Ownable *c = nullptr;
                std::vector<Cell *> ownedProperties = p->getOwnedProperties();
                for (int i = 0; i < ownedProperties.size(); i++) {
                    if (ownedProperties[i]->getName() == property) {
                        c = dynamic_cast<Ownable*>(ownedProperties[i]);
                    }
                }
                if (c == nullptr) {
                    cout << "You do not own this property, you cannot mortgage it." << endl;
                } else {
                    c->mortgage();
                }
            } else if (cmd == "unmortgage") {
                string property;
                cin >> property;
                Ownable *c = nullptr;
                std::vector<Cell *> ownedProperties = p->getOwnedProperties();
                for (int i = 0; i < ownedProperties.size(); i++) {
                    if (ownedProperties[i]->getName() == property) {
                        c = dynamic_cast<Ownable*>(ownedProperties[i]);
                    }
                }
                if (c == nullptr) {
                    cout << "You do not own this property, you cannot unmortgage it." << endl;
                } else {
                    c->unMortgage();
                }
            } else if (cmd == "assets") {
                p->printAssets();
            } else if (cmd == "bankrupt") {
                // TODO p->bankrupt();
            } else if (cmd == "all") {
                for (int i = 0; i < players.size(); i++) {
                    players[i]->printAssets();
                }
            } else if (cmd == "save") {
                string filename;
                cin >> filename;
                b.saveGame(filename);
            } else {
                cout << "Invalid command, please enter a valid command." << endl;
            }
        }
    } else if (loadfile != "") {
        b.loadGame(loadfile);
    }
    
    cout << b;
}