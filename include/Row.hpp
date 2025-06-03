#pragma once
#include "Cell.hpp"
#include <vector>


/**
 * @class Row
 * @brief Represents a row in a table, containing a sequence of cells.
 *
 * The Row class manages a collection of Cell pointers, providing methods for adding,
 * accessing, modifying, and displaying cell values within a row.
 */
class Row {
private:
    std::vector<Cell*> cells; ///< The cells contained in this row.

public:
    Row();

    /**
     * @brief Copy constructor for Row. Performs a deep copy of all cells.
     * @param other The Row to copy from.
     */
    Row(const Row& other);

    /**
     * @brief Assignment operator for Row. Performs a deep copy of all cells.
     * @param other The Row to assign from.
     * @return Reference to this Row.
     */
    Row& operator=(const Row& other);
    ~Row();

    /**
     * @brief Adds a cell to the end of the row.
     * @param cell Pointer to the cell to add.
     */
    void addCell(Cell* cell);

    /**
     * @brief Gets the cell at the specified index.
     * @param index The index of the cell.
     * @return Pointer to the cell at the given index.
     * @throws std::out_of_range If the index is invalid.
     */
    Cell* getCell(size_t index) const;

    /**
     * @brief Sets the cell at the specified index, deleting the old cell.
     * @param index The index of the cell to set.
     * @param cell Pointer to the new cell.
     * @throws std::out_of_range If the index is invalid.
     */
    void setCell(size_t index, Cell* cell); 

    /**
     * @brief Returns a string representation of the row.
     * @return The string representation of the row's cell values.
     */
    std::string toString() const;
};