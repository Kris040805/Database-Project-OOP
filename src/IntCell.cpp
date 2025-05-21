#include <iostream>
#include "IntCell.hpp"
#include <string>


IntCell::IntCell(int value) : value(value) {}

IntCell::IntCell(const IntCell& other) : value(other.value) {}

IntCell& IntCell::operator=(const IntCell& other) {
    if (this != &other) {
        value = other.value;
    }
    return *this;
}

int IntCell::compare(const Cell& other) const {
    if (other.getType() != ColumnType::Int)
    {
        throw std::invalid_argument("Cannot compare IntCell with non-IntCell.");
    }

    const IntCell& otherInt = static_cast<const IntCell&>(other);

    if (value < otherInt.value) return -1;
    if (value > otherInt.value) return 1;
    return 0;
}


ColumnType IntCell::getType() const{
    return ColumnType::Int;
}

std::string IntCell::toString() const {
    return std::to_string(value);
}

Cell* IntCell::clone() const {
    return new IntCell(*this);
}