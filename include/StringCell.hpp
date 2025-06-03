#pragma once
#include "Cell.hpp"
#include <string>


/**
 * @class StringCell
 * @brief Represents a cell containing a string value.
 *
 * StringCell implements the Cell interface for storing and manipulating string values in a table.
 */
class StringCell : public Cell {
private:
    std::string str; ///< The string value stored in the cell.

public:

    /**
     * @brief Constructs a StringCell with the given string value.
     * @param str The string value to store.
     */
    StringCell(const std::string& str);

    /**
     * @brief Copy constructor for StringCell.
     * @param other The StringCell to copy from.
     */
    StringCell(const StringCell& other);

    /**
     * @brief Assignment operator for StringCell.
     * @param other The StringCell to assign from.
     * @return Reference to this StringCell.
     */
    StringCell& operator=(const StringCell& other);


    /**
     * @brief Compares this cell with another cell.
     * @param other The cell to compare with.
     * @return An integer less than, equal to, or greater than zero if this cell is less than, equal to, or greater than the other cell.
     * @throws std::invalid_argument If the other cell is not a StringCell.
     */
    int compare(const Cell& other) const override;

    /**
     * @brief Returns the type of this cell.
     * @return ColumnType::String.
     */
    ColumnType getType() const override;

    /**
     * @brief Converts the cell's value to a string.
     * @return The string value stored in the cell.
     */
    std::string toString() const override;

    /**
     * @brief Creates a deep copy of the cell.
     * @return A pointer to the newly cloned StringCell.
     */
    Cell* clone() const override;
};