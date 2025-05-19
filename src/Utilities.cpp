#include "Utilities.hpp"
#include "IntCell.hpp"
#include "DoubleCell.hpp"
#include "StringCell.hpp"
#include "NullCell.hpp"
#include <cctype>

bool isInteger(const std::string& str){
    if (str.empty())
    {
        return false;
    }
    
    size_t i = ((str[0] == '-') ? 1 : 0); 
    if (i == str.size())
    {
        return false;
    }
    
    for (; i < str.size(); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

bool isDouble(const std::string& str){
    size_t dotCounter = 0;
    size_t i = ((str[0] == '-') ? 1 : 0);
    bool hasDigit = false;

    for (; i < str.size(); i++)
    {
        if (str[i] == '.')
        {
            if (++dotCounter > 1)
            {
                return false;
            }
        } else if (!isdigit(str[i]))
        {
            return false;
        } else {
            hasDigit = true;
        }
    }
    
    if (str.empty() || str.back() == '.')
    {
        return false;
    }
    
    return hasDigit && dotCounter == 1;
}

bool isString(const std::string& str){
    return str.size() >= 2 && str.front() == '"' && str.back() == '"';
}

std::string decodeEscapedStr(const std::string& str){
    std::string result;
    for (size_t i = 1; i < str.size() - 1; ++i) {
        if (str[i] == '\\' && i < str.size() - 1) 
        {
            if (str[i + 1] == '\\') result += '\\';
            else if (str[i + 1] == '"') result += '"';
            ++i;
        } else {
            result += str[i];
        }
    }
    return result;
}

Cell* createCellFromStr(const std::string& str){
    if (str == "NULL")
    {
        return new NullCell();
    }
    
    if (isInteger(str))
    {
        return new IntCell(std::stoi(str));
    }

    if (isDouble(str))
    {
        return new DoubleCell(std::stod(str));
    }

    if (isString(str))
    {
        return new StringCell(decodeEscapedStr(str));
    }

    return new NullCell();
}