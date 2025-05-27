#include "Utilities.hpp"
#include "IntCell.hpp"
#include "DoubleCell.hpp"
#include "StringCell.hpp"
#include "NullCell.hpp"
#include "Row.hpp"
#include "Table.hpp"
#include <cctype>
#include <vector>
#include <iostream>



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

void printRowsPaged(const std::vector<const Row*>& rows, const Table& tab, const std::string& title){
    const size_t rowsPerPage = 10;
    size_t currentPage = 0;
    size_t totalPages = (rows.size() + rowsPerPage - 1) / rowsPerPage;

    std::string input;

    while (true)
    {
        //От интернет
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        std::cout << "~~~ " << title << " | Page " << (currentPage + 1) 
                  << " of " << (totalPages == 0 ? 1 : totalPages) << " ~~~\n\n";
        
        //Принтиране на имена на колоните
        std::cout << "№ | ";
        for (size_t i = 0; i < tab.getColumnCount(); i++)
        {
            std::cout << tab.getColumnName(i);
            if (i < tab.getColumnCount() - 1)
            {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;

        //Принтиране на редовете
        size_t start = currentPage * rowsPerPage;
        size_t end = std::min(start + rowsPerPage, rows.size());

        for (size_t i = start; i < end; i++)
        {
            std::cout << i + 1 << ". " << rows[i]->toString() << std::endl;
        }
        std::cout << std::endl;
        
        while (true)
        {
            std::cout << "[n]ext, [p]revious, [e]xit";
            std::getline(std::cin, input);

            if (input == "n" || input == "next")
            {
                if (currentPage < totalPages - 1)
                {
                    currentPage++;
                }
                else
                {
                    std::cout << "You are already on the last page." << std::endl;
                }
                break;
            }
            else if (input == "p" || input == "previous")
            {
                if (currentPage > 0)
                {
                    currentPage--;
                }
                else
                {
                    std::cout << "You are already on the first page." << std::endl;
                }
                break;
            }
            else if (input == "e" || input == "exit")
            {
                return;
            }
            else
            {
                std::cout << "Invalid input. Please enter next, prev or exit." << std::endl;
            }
        }
    }
}

double getValueFromCell(const Cell* cell){
    if (cell->getType() == ColumnType::Int)
    {
        return dynamic_cast<const IntCell*>(cell)->getValue();
    } else {
        return dynamic_cast<const DoubleCell*>(cell)->getValue();
    }
}

double aggregateSum(const std::vector<const Cell*>& cells){
    double sum = 0.0;
    for (const Cell* cell : cells){
        sum += getValueFromCell(cell);
    }
    return sum;
}

double aggregateProduct(const std::vector<const Cell*>& cells){
    double prod = 1.0;
    for (const Cell* cell : cells){
        prod *= getValueFromCell(cell);
    }
    return prod;
}

double aggregateMin(const std::vector<const Cell*>& cells){
    double min = getValueFromCell(cells[0]);
    for (size_t i = 1; i < cells.size(); i++)
    {
        min = std::min(min, getValueFromCell(cells[i]));
    }
    return min;
}

double aggregateMax(const std::vector<const Cell*>& cells){
    double max = getValueFromCell(cells[0]);
    for (size_t i = 1; i < cells.size(); i++)
    {
        max = std::max(max, getValueFromCell(cells[i]));
    }
    return max;
}

std::vector<std::string> parseCSVLine(const std::string& line){
    std::vector<std::string> result;
    std::string current;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char ch = line[i];

        if (ch == '"') {
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                current += '"';
                ++i;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (ch == ',' && !inQuotes) {
            result.push_back(current);
            current.clear();
        } else {
            current += ch;
        }
    }

    result.push_back(current);
    return result;
}