#include "Row.hpp"

Row::Row() {} 

Row::Row(const Row& other) {
    for (Cell* cell : other.cells)
    {
        cells.push_back(cell->clone());
    }
}

Row& Row::operator=(const Row& other) {
    if (this != &other)
    {
        for (size_t i = 0; i < cells.size(); i++)
        {
            delete cells[i];
        }
        
        cells.clear();

        for (size_t i = 0; i < other.cells.size(); i++)
        {
            cells.push_back(other.cells[i]->clone());
        }
        
    }
    return *this;
}

Row::~Row() {
    for (size_t i = 0; i < cells.size(); i++)
    {
        delete cells[i];
    }
}

void Row::addCell(Cell* cell) {
    cells.push_back(cell);
}

Cell* Row::getCell(size_t index) const {
    if (index >= 0 && index < cells.size())
    {
        return cells[index];
    }
    
    return nullptr; 
}

std::string Row::toString() const {
    std::string result;
    for (size_t i = 0; i < cells.size(); i++)
    {
        result += cells[i]->toString();
        if (i < cells.size() - 1)
        {
            result += " | ";
        }
    }
    
    return result;
}