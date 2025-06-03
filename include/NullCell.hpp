#pragma once
#include "Cell.hpp"
#include <string>

/**
 * @class NullCell
 * @brief Represents a cell containing a null value.
 *
 * NullCell implements the Cell interface for representing missing or undefined values in a table.
 */
class NullCell : public Cell {
public:
    NullCell() = default;

    /**
     * @brief Compares this cell with another cell.
     * @param other The cell to compare with.
     * @return Zero if both cells are NullCell, otherwise throws std::invalid_argument.
     * @throws std::invalid_argument If the other cell is not a NullCell.
     */
    int compare(const Cell& other) const override;

    /**
     * @brief Returns the type of this cell.
     * @return ColumnType::Null.
     */
    ColumnType getType() const override;

    /**
     * @brief Converts the cell's value to a string.
     * @return The string "NULL".
     */
    std::string toString() const override;

    /**
     * @brief Creates a deep copy of the NullCell.
     * @return A pointer to a new NullCell instance.
     */
    Cell* clone() const override;
};