#ifndef CELL_H
#define CELL_H
#include "observer.h"
#include "subject.h"
#include <string>
#include "state.h"

class Player;
class Board;

enum OwnableType{Academic, Residence, Gym, Nonownable};


class Cell: public Subject{
protected:
    std::string name;
    int posn;
    int i;
    int j;
    Board &board;
    bool wasSuccesful;
    bool ownable;

    // Only ownable properties will use the following attributes; non-ownable should use just cellName and posn, and the Player obj decides what to do from there.
    OwnableType otype;
    Player *ownedBy = nullptr;
    int improveCount = 0;
    int price;
    bool isMortgaged = false;
public:
    Cell(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price);
    Player *getOwnedBy();
    OwnableType getOtype();
    void setOwnedBy(Player *ownedBy);
    virtual std::string getName() override;
    int getPosn();
    int getI();
    int getJ();
    bool getSuccesful();
    void setSuccesful(bool wasSuccesful);
    bool getOwnable();
    int getImproveCount();
    void setImproveCount(int newImprove);
    int getPrice();
    bool getMortgaged();
    void setMortgaged(bool isMortgaged);
    virtual void event(Player *p);


};



#endif
