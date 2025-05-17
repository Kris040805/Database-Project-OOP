#include "ColumnType.hpp"

ColumnType parseColType(const std::string& strType){
    if (strType == "int") return ColumnType::Int;
    if (strType == "double") return ColumnType::Double;
    if (strType == "string") return ColumnType::String;
    return ColumnType::Null;
}

std::string colTypeToString(ColumnType colType){
    switch (colType)
    {
    case ColumnType::Int:
        return "int";

    case ColumnType::Double:
        return "double";

    case ColumnType::String:
        return "string";

    case ColumnType::Null:
        return "null";
    }
    return "Invalid type!";
}