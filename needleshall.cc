#include "needleshall.h"

class Cell;

NeedlesHall::NeedlesHall(Board &board, std::string name, int pos, int i, int j): NonOwnable{board, name, pos, i, j} {}