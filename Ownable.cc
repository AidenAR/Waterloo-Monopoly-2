//
// Created by aiden on 03/04/2023.
//

#include "ownable.h"


Ownable::Ownable(Board &board, std::string name, int posn, int i, int j, bool ownable, OwnableType otype, int price) :
    Cell(board, name, posn, i, j, ownable, otype, price) {}
