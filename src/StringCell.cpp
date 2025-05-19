#include <iostream>
#include "StringCell.hpp"
#include <string>

StringCell::StringCell(const std::string& str) : str(str) {}

StringCell::StringCell(const StringCell& other) : str(other.str) {}

StringCell& StringCell::operator=(const StringCell& other) {
    if (this != &other) {
        str = other.str;
    }
    return *this;
}

ColumnType StringCell::getType() const{
    return ColumnType::String;
}

std::string StringCell::toString() const {
    return str;
}

Cell* StringCell::clone() const {
    return new StringCell(*this);
}
