#pragma once
#include "Cell.hpp"
#include <string>

class NullCell : public Cell {
public:
    NullCell() = default;
    std::string toString() const override;
    Cell* clone() const override;
};