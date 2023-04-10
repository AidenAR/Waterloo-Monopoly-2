#include "nonownable.h"
#include "player.h"
#include <iostream>

using namespace std;


NonOwnable::NonOwnable(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price): 
    Cell(board, name, posn, i, j, ownable, otype, price) {}

void NonOwnable::event(Player *p) {
    if (name == "COLLECT OSAP") {
            p->addFunds(200);
    } else if (name == "DC Tims Line") {
        if (p->getTimsJail()) {
            if (p->getRollRims() > 0) {
                cout << "Do you want to use a roll up the rim cup to get out of jail?[y/n]" << endl;
                string response;
                cin >> response;
                if (response == "y") {
                    p->subtractRollRims();
                    // TODO: set player state to not in jail and set jailTurns to 0 
                    p->freePlayerFromTimsJail();
                } 
            } else if (p->getJailTurns() == 3) {
                cout << "You have been in jail for 3 turns, you must pay $50 to get out" << endl;
                p->subFunds(50);
                //TODO: if player doesnt have funds for it, then auctioning time!
                p->subtractRollRims();
            } else {
                cout << "You must roll doubles or pay $50 to get out of jail" << endl;
                cout << "Do you want to roll or pay?[roll/pay]" << endl;
                string response;
                cin >> response;

                while (true) {
                    if (response == "roll") {
                        vector<int> roll{Board().rollDice()};
                        if (roll[0] == roll[1]) {
                            p->freePlayerFromTimsJail();
                        } else{
                            cout << "Unfortunatley didnt roll doubles, sstaying in Jail );";
                        }
                        break;
                    } else if (response == "pay") {
                        p->subFunds(50);
                        break;
                    } else {
                        cout << "Please enter valid response" << endl;
                    }
                }

            }
        }
    } else if (name == "GoToTims") {
        cout << "Its Jail Time!" << endl;
        p->setPlayerPosn(10);
        p->setTimsJail(true);
        p->setJailTurns(0);
        notifyObservers();
    } else if (name == "CoopFee") {
        p->subFunds(150);
    } else if (name == "Tuiton") {
        cout << "Do you want to pay $300 tuition or 10% of your total worth?[pay/10%]" << endl;
        string response;
        cin >> response;
        if (response == "pay") {
            p->subFunds(300);
        } else {
            p->subFunds(p->playerAssetsWorth() * 0.1);
        }

    } else if (name == "SLC") {
        p->addRollRims();

        int randNum = rand() % 24;
        
        // lmao these probabilities are fs way off but idc tbh
        if (randNum < 1) {
            p->moveForward(10); // DC tims line
            //TODO: put player in jail
        } else if (randNum < 5) {
            p->moveForward(-2);
            //
        } else if (randNum < 9) {
            p->moveForward(-1);
            //
        } else if (randNum < 13) {
            p->moveForward(+2);
            //
        } else if (randNum < 17) {
            p->moveForward(+3);
            //
        } else if (randNum < 20) {
            p->moveForward(-2);
            //
        } else if (randNum < 23) {
            p->moveForward(-2);
            //
        } else if (randNum < 24) {
            p->moveForward(0);
            //
        } 
        notifyObservers();


    } else if (name == "NEEDLES HALL") {
        p->addRollRims();
        

        int randNum = rand() % 18;
        
        if (randNum < 1) {
            p->subFunds(200);
        } else if (randNum < 3) {
            p->subFunds(100);
        } else if (randNum < 6) {
            p->subFunds(50);
        } else if (randNum <  12) {
            p->addFunds(25);
        } else if (randNum < 15) {
            p->addFunds(50);
        } else if (randNum < 17) {
            p->addFunds(100);
        } else if (randNum < 18) {
            p->addFunds(200);
        }
    }
}