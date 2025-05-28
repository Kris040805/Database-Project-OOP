#include "../include/ColumnType.hpp"

ColumnType parseColType(const std::string& strType){
    if (strType == "Int") return ColumnType::Int;
    if (strType == "Double") return ColumnType::Double;
    if (strType == "String") return ColumnType::String;
    return ColumnType::Null;
}

std::string colTypeToString(ColumnType colType){
    switch (colType)
    {
    case ColumnType::Int:
        return "Int";

    case ColumnType::Double:
        return "Double";

    case ColumnType::String:
        return "String";

    case ColumnType::Null:
        return "NULL";
    }
    return "Invalid type!";
}