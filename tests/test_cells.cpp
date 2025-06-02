#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "../include/Cell.hpp"
#include "../include/IntCell.hpp"
#include "../include/DoubleCell.hpp"
#include "../include/StringCell.hpp"
#include "../include/NullCell.hpp"

TEST_CASE("IntCell basic") {
    IntCell cell(42);
    CHECK(cell.getValue() == 42);
    CHECK(cell.getType() == ColumnType::Int);
    CHECK(cell.toString() == "42");
    
    IntCell cell2(100);
    CHECK(cell.compare(cell2) < 0); // 42 < 100
}

TEST_CASE("StringCell basic") {
    StringCell cell("Hello");
    CHECK(cell.getType() == ColumnType::String);
    CHECK(cell.toString() == "Hello");
}

TEST_CASE("DoubleCell basic") {
    DoubleCell cell(5.24);
    CHECK(cell.getType() == ColumnType::Double);
    
    DoubleCell cell2(2.71);
    CHECK(cell.compare(cell2) > 0); // 3.14 > 2.71
}

TEST_CASE("NullCell basic") {
    NullCell cell;
    CHECK(cell.getType() == ColumnType::Null);
    CHECK(cell.toString() == "NULL");
}