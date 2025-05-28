#include <iostream>
#include "../include/NullCell.hpp"
#include "../include/Cell.hpp"
#include "../include/ColumnType.hpp"
#include <stdexcept>
#include <string>

int NullCell::compare(const Cell& other) const{
    if (other.getType() != ColumnType::Null)
    {
        throw std::invalid_argument("Cannot compare NullCell with non-NullCell.");
    }

    return 0;
}

ColumnType NullCell::getType() const{
    return ColumnType::Null;
}

std::string NullCell::toString() const {
    return "NULL";
}

Cell* NullCell::clone() const {
    return new NullCell();
}