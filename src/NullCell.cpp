#include <iostream>
#include "NullCell.hpp"
#include <string>

ColumnType NullCell::getType() const{
    return ColumnType::Null;
}

std::string NullCell::toString() const {
    return "NULL";
}

Cell* NullCell::clone() const {
    return new NullCell();
}