#include "cell.h"
#include "board.h"


template <typename InfoType, typename StateType> class Subject;

Cell::Cell(Board &board, std::string name, int posn, int i, int j) : board{board}, name{name}, posn{posn}, i{i}, j{j} {
    
}