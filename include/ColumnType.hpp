#pragma once 
#include <string>

enum class ColumnType {
    Int,
    Double,
    String,
    Null
};

ColumnType parseColType(const std::string& strType);
std::string colTypeToString(ColumnType colType);