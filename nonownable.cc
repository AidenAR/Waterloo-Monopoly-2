#include "nonownable.h"


template <typename InfoType, typename StateType> class Subject;


NonOwnable::NonOwnable(Board &board, std::string name, int posn, int i, int j): Cell(board, name, posn, i, j) {}