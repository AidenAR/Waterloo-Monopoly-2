#include "gototims.h"

class Cell;

GoToTims::GoToTims(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price): NonOwnable{board, name, posn, i, j, ownable, otype, price} {}