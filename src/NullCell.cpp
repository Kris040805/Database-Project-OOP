#include <iostream>
#include "NullCell.hpp"
#include <string>

std::string NullCell::toString() const {
    return "NULL";
}

Cell* NullCell::clone() const {
    return new NullCell();
}