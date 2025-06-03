#pragma once
#include "Cell.hpp"
#include <string>
#include "Table.hpp"
#include "Row.hpp"
#include <vector>

/**
 * @brief Checks if a string represents a valid integer.
 * @param str The string to check.
 * @return True if the string is an integer, false otherwise.
 */
bool isInteger(const std::string& str);

/**
 * @brief Checks if a string represents a valid double.
 * @param str The string to check.
 * @return True if the string is a double, false otherwise.
 */
bool isDouble(const std::string& str);

/**
 * @brief Checks if a string represents a valid string value (e.g., quoted).
 * @param str The string to check.
 * @return True if the string is a valid string value, false otherwise.
 */
bool isString(const std::string& str);


/**
 * @brief Decodes a string with escape sequences.
 * @param str The escaped string.
 * @return The decoded string.
 */
std::string decodeEscapedStr(const std::string& str);


/**
 * @brief Creates a Cell object from a string representation with factory.
 * @param str The string to convert.
 * @return Pointer to a new Cell object.
 */
Cell* createCellFromStr(const std::string& str);


/**
 * @brief Prints rows in a paged format.
 * @param rows The rows to print.
 * @param table The table structure for column info.
 * @param title The title to display.
 */
void printRowsPaged(const std::vector<const Row*>& rows, const Table& table, const std::string& title);


/**
 * @brief Extracts a double value from a Cell.
 * @param cell Pointer to the cell.
 * @return The value as double.
 */
double getValueFromCell(const Cell* cell);

/**
 * @brief Calculates the sum of values in a vector of cells.
 * @param cells The cells to sum.
 * @return The sum as double.
 */
double aggregateSum(const std::vector<const Cell*>& cells);

/**
 * @brief Calculates the product of values in a vector of cells.
 * @param cells The cells to multiply.
 * @return The product as double.
 */
double aggregateProduct(const std::vector<const Cell*>& cells);

/**
 * @brief Finds the minimum value in a vector of cells.
 * @param cells The cells to check.
 * @return The minimum value as double.
 */
double aggregateMin(const std::vector<const Cell*>& cells);

/**
 * @brief Finds the maximum value in a vector of cells.
 * @param cells The cells to check.
 * @return The maximum value as double.
 */
double aggregateMax(const std::vector<const Cell*>& cells);

/**
 * @brief Parses a CSV line into a vector of strings.
 * @param line The CSV line.
 * @return Vector of parsed values.
 */
std::vector<std::string> parseCSVLine(const std::string& line);