#pragma once
#include "Cell.hpp"


/**
 * @class DoubleCell
 * @brief Represents a cell containing a double-precision floating-point value.
 *
 * DoubleCell implements the Cell interface for storing and manipulating double values in a table.
 */
class DoubleCell : public Cell {
private:
    double value; ///< The double value stored in the cell.

public:
    /**
     * @brief Constructs a DoubleCell with a given double value.
     * @param value The double value to store in the cell.
     */
    DoubleCell(double value);

    /**
     * @brief Copy constructor for DoubleCell.
     * @param other The DoubleCell to copy from.
     */
    DoubleCell(const DoubleCell& other);

    /**
     * @brief Assignment operator for DoubleCell.
     * @param other The DoubleCell to assign from.
     * @return Reference to this DoubleCell.
     */
    DoubleCell& operator=(const DoubleCell& other);
    
    /**
     * @brief Compares this cell with another cell.
     * @param other The cell to compare with.
     * @return An integer less than, equal to, or greater than zero if this cell is less than, equal to, or greater than the other cell.
     * @throws std::invalid_argument If the other cell is not a DoubleCell.
     */
    int compare(const Cell& other) const override;

    /**
     * @brief Gets the double value stored in this cell.
     * @return The double value.
     */
    double getValue() const;
    /**
     * @brief Returns the type of this cell.
     * @return The ColumnType::Double.
     */
    ColumnType getType() const override;

    /**
     * @brief Converts the cell's value to a string.
     * @return The string representation of the value.
     */
    std::string toString() const override;

    /**
     * @brief Creates a deep copy of the cell.
     * @return A pointer to the newly cloned DoubleCell.
     */
    Cell* clone() const override;
};