#pragma once
#include "Cell.hpp"
#include <string>
#include "Table.hpp"
#include "Row.hpp"
#include <vector>

bool isInteger(const std::string& str);
bool isDouble(const std::string& str);
bool isString(const std::string& str);

std::string decodeEscapedStr(const std::string& str);

Cell* createCellFromStr(const std::string& str);

void printRowsPaged(const std::vector<const Row*>& rows, const Table& table, const std::string& title);

double getValueFromCell(const Cell* cell);
double aggregateSum(const std::vector<const Cell*>& cells);
double aggregateProduct(const std::vector<const Cell*>& cells);
double aggregateMin(const std::vector<const Cell*>& cells);
double aggregateMax(const std::vector<const Cell*>& cells);

std::vector<std::string> parseCSVLine(const std::string& line);