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

std::string DoubleCell::toString() const {
    return std::to_string(value);
}

Cell* DoubleCell::clone() const {
    return new DoubleCell(*this);
}