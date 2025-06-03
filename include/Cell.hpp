#pragma once
#include <string>
#include "ColumnType.hpp"


/**
 * @class Cell
 * @brief Defines the abstract base class Cell for representing a cell in a database table.
 * 
 * The Cell class provides a common interface for different types of cells (IntCell, DoubleCell, StringCell, NullCell) in a database table
 * and defines the necessary methods for comparison, type retrieval, string conversion, and cloning.
 */
class Cell {
    public:
    Cell() = default;
    Cell(const Cell&) = default;
    Cell& operator=(const Cell&) = default;
    virtual ~Cell() = default;

    /**
     * @brief Compares this cell with another cell.
     * 
     * @param other The cell to compare with.
     * @return int A negative value if this cell is less than the other, zero if they are equal, and a positive value if this cell is greater.
     */
    virtual int compare(const Cell& other) const = 0;
    
    /**
     * @brief Returns the type of this cell.
     * @return The ColumnType of this cell.
     * */
    virtual ColumnType getType() const = 0;

    /**
     * @brief Converts this cell's value to a string.
     * @return A string representation of this cell's value.
     */
    virtual std::string toString() const = 0;

    /**
     * @brief Creates a deep copy of the cell.
     * @return A pointer to the newly cloned cell.
     */
    virtual Cell* clone() const = 0;
};