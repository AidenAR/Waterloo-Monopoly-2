#include "dctimsline.h"

class Cell;


DCTimsLine::DCTimsLine(Board &board, std::string name, int pos, int i, int j): NonOwnable{board, name, pos, i, j} {}
