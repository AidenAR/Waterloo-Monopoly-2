#include "tuition.h"

class Cell;

Tuition::Tuition(Board &board, std::string name, int pos, int i, int j): NonOwnable{board, name, pos, i, j} {}