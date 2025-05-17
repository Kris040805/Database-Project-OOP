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

std::string IntCell::toString() const {
    return std::to_string(value);
}

Cell* IntCell::clone() const {
    return new IntCell(*this);
}