#pragma once
#include "Cell.hpp"
#include <vector>

class Row {
private:
    std::vector<Cell*> cells;

public:
    Row();
    Row(const Row& other);
    Row& operator=(const Row& other);
    ~Row();

    void addCell(Cell* cell);
    Cell* getCell(size_t index) const;
    std::string toString() const;
};