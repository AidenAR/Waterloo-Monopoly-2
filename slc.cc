#include "slc.h"

class Cell;

Slc::Slc(Board &board, std::string name, int pos, int i, int j): NonOwnable{board, name, pos, i, j} {}
