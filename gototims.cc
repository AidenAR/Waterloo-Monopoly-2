#include "gototims.h"

class Cell;

GoToTims::GoToTims(Board &board, std::string name, int pos, int i, int j): NonOwnable{board, name, pos, i, j} {}