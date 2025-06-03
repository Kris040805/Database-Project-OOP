#pragma once
#include "Cell.hpp"


/**
 * @class IntCell
 * @brief Represents a cell containing an integer value.
 *
 * IntCell implements the Cell interface for storing and manipulating integer values in a table.
 */
class IntCell : public Cell {
private:
    int value; ///< The integer value stored in the cell.

public:

    /**
     * @brief Constructs an IntCell with the given value.
     * @param value The integer value to store.
     */
    IntCell(int value);

    /**
     * @brief Assignment operator for IntCell.
     * @param other The IntCell to assign from.
     * @return Reference to this IntCell.
     */
    IntCell& operator=(const IntCell& other);

    /**
     * @brief Copy constructor for IntCell.
     * @param other The IntCell to copy from.
     */
    IntCell(const IntCell& other);

    /**
     * @brief Compares this cell with another cell.
     * @param other The cell to compare with.
     * @return An integer less than, equal to, or greater than zero if this cell is less than, equal to, or greater than the other cell.
     * @throws std::invalid_argument If the other cell is not an IntCell.
     */
    int compare(const Cell& other) const override;

    /**
     * @brief Gets the integer value stored in this cell.
     * @return The integer value.
     */
    int getValue() const;

    /**
     * @brief Returns the type of this cell.
     * @return ColumnType::Int.
     */
    ColumnType getType() const override;

    /**
     * @brief Converts the cell's value to a string.
     * @return The string representation of the value.
     */
    std::string toString() const override;

    /**
     * @brief Creates a deep copy of the IntCell.
     * @return A pointer to the newly cloned IntCell.
     */
    Cell* clone() const override;
};