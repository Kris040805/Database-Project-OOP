#include <iostream>
#include "DoubleCell.hpp"
#include <string>

DoubleCell::DoubleCell(double value) : value(value) {}

DoubleCell::DoubleCell(const DoubleCell& other) : value(other.value) {}

DoubleCell& DoubleCell::operator=(const DoubleCell& other) {
    if (this != &other) {
        value = other.value;
    }
    return *this;
}

int DoubleCell::compare(const Cell& other) const{
    if (other.getType() != ColumnType::Double)
    {
        throw std::invalid_argument("Cannot compare DoubleCell with non-DoubleCell.");
    }

    const DoubleCell& otherDouble = static_cast<const DoubleCell&>(other);

    if (value < otherDouble.value) return -1;
    if (value > otherDouble.value) return 1;
    return 0;
}


ColumnType DoubleCell::getType() const{
    return ColumnType::Double;
}

std::string DoubleCell::toString() const {
    return std::to_string(value);
}

Cell* DoubleCell::clone() const {
    return new DoubleCell(*this);
}