#pragma once 
#include <string>

/**
 * @enum ColumnType
 * @brief Represents the suported column types in table columns.
 */
enum class ColumnType {
    Int,
    Double,
    String,
    Null
};

/**
 * @brief Parses a string representation of a column type and returns the corresponding ColumnType enum value.
 * 
 * @param strType The string representation of the column type (e.g., "Int", "Double", "String").
 * @return The coresponding ColumnType value, or ColumnType::Null if the string is invalid.
 */
ColumnType parseColType(const std::string& strType);

/**
 * @brief Converts a ColumnType enum value to its string representation.
 * 
 * @param colType The ColumnType enum value to convert.
 * @return The std::string representation of the column type.
 */
std::string colTypeToString(ColumnType colType);