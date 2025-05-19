#pragma once
#include "Cell.hpp"
#include <string>

bool isInteger(const std::string& str);
bool isDouble(const std::string& str);
bool isString(const std::string& str);

std::string decodeEscapedStr(const std::string& str);

Cell* createCellFromStr(const std::string& str);