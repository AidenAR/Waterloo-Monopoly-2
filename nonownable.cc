#include "nonownable.h"
#include "player.h"

template <typename InfoType, typename StateType> class Subject;


NonOwnable::NonOwnable(Board &board, std::string name, int posn, int i, int j): Cell(board, name, posn, i, j) {}

void NonOwnable::notify(std::shared_ptr<Subject<Info, State>> whoFrom) {
    
    // As this is a Cell, we are guaranteed only Players will notify it. 
    // Thus, we can assume that we can obtain a State object from it.
    State state = *whoFrom->getState();


    // What cases should we even respond to it?? 
    // We never have to deal w purchase, mortgage, etc
    // Just have to deal with when we land on it, ORR, if we move over it. 
    switch (state.type)
    {
    case StateType::Landed:
        notifyObservers();
        break;
    case StateType::Move:
        // Which unownable cells care about whether cells move ontop of it???

        if (info.cellName == "OCollectOsapSAP") {
            notifyObservers();
        }
        break;
    
    default:
        break;
    }
}