#include "goosenesting.h"

class Cell;

Goose::Goose(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price): NonOwnable{board, name, posn, i, j, ownable, otype, price} {}