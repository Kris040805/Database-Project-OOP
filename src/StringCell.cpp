#include <iostream>
#include "../include/StringCell.hpp"
#include "../include/Cell.hpp"
#include "../include/ColumnType.hpp"
#include <string>

StringCell::StringCell(const std::string& str) : str(str) {}

StringCell::StringCell(const StringCell& other) : str(other.str) {}

StringCell& StringCell::operator=(const StringCell& other) {
    if (this != &other) {
        str = other.str;
    }
    return *this;
}

int StringCell::compare(const Cell& other) const {
    if (other.getType() != ColumnType::String)
    {
        throw std::invalid_argument("Cannot compare StringCell with non-StringCell.");
    }

    const StringCell& otherStr = static_cast<const StringCell&>(other);

    if (str < otherStr.str) return -1;
    if (str > otherStr.str) return 1;
    return 0;
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
