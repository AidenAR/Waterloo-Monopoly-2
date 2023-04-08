#include "goosenesting.h"

class Cell;

Goose::Goose(Board &board, std::string name, int pos, int i, int j): NonOwnable{board, name, pos, i, j} {}