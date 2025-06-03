#pragma once
#include "Cell.hpp"
#include "NullCell.hpp"
#include "ColumnType.hpp"
#include "Row.hpp"
#include <vector>
#include <string>


/**
 * @class Table
 * @brief Represents a table in the database, containing columns and rows.
 *
 * The Table class manages the structure (column names and types) and the data (rows) of a table.
 * It provides methods for adding columns, inserting and deleting rows, and accessing table metadata.
 */
class Table {
private:
    std::string name; ///< The name of the table.
    std::vector<std::string> columnNames; ///< The names of the columns.
    std::vector<ColumnType> columnTypes; ///< The types of the columns.
    std::vector<Row> rows; ///< The rows of the table.

public:
    Table();

    /**
     * @brief Constructs a Table with the given name.
     * @param name The name of the table.
     */
    Table(const std::string& name);

    /**
     * @brief Sets the name of the table.
     * @param name The new name for the table.
     */
    void setName(const std::string& name);

    /**
     * @brief Gets the name of the table.
     * @return The name of the table.
     */
    const std::string& getName() const;


    /**
     * @brief Adds a new column to the table.
     * @param colName The name of the new column.
     * @param colType The type of the new column.
     * @throws std::invalid_argument If a column with the same name already exists.
     */
    void addColumn(const std::string& colName, ColumnType colType);

    /**
     * @brief Inserts a new row into the table.
     * @param row The row to insert.
     */
    void insertRow(const Row& row);

    /**
     * @brief Deletes the row at the specified index.
     * @param index The index of the row to delete.
     * @throws std::out_of_range If the index is invalid.
     */
    void deleteRow(size_t index);

    /**
     * @brief Gets a constant reference to the row at the specified index.
     * @param index The index of the row.
     * @return Constant reference to the row.
     * @throws std::out_of_range If the index is invalid.
     */
    const Row& getRow(size_t index) const;

    /**
     * @brief Gets a reference to the row at the specified index.
     * @param index The index of the row.
     * @return Reference to the row.
     * @throws std::out_of_range If the index is invalid.
     */
    Row& getRow(size_t index);

    /**
     * @brief Returns the number of rows in the table.
     * @return The row count.
     */
    size_t getRowCount() const;

    /**
     * @brief Returns the number of columns in the table.
     * @return The column count.
     */
    size_t getColumnCount() const;

    /**
     * @brief Gets the type of the column at the specified index.
     * @param index The index of the column.
     * @return The column type.
     * @throws std::out_of_range If the index is invalid.
     */
    ColumnType getColumnType(size_t index) const;

    /**
     * @brief Gets the name of the column at the specified index.
     * @param index The index of the column.
     * @return The column name.
     * @throws std::out_of_range If the index is invalid.
     */
    const std::string& getColumnName(size_t index) const;

    /**
     * @brief Gets the index of the column with the specified name.
     * @param colName The name of the column.
     * @return The index of the column.
     * @throws std::invalid_argument If the column does not exist.
     */
    size_t getColumnIndex(const std::string& colName) const;

    /**
     * @brief Returns a string representation of the table.
     * @return The string representation of the table.
     */
    std::string toString() const;
};