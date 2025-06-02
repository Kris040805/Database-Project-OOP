#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "../include/IntCell.hpp"
#include "../include/StringCell.hpp"
#include "../include/Row.hpp"
#include "../include/Table.hpp"



TEST_CASE("Table and row basic operations") {
    Table t("students");
    t.addColumn("id", ColumnType::Int);
    t.addColumn("name", ColumnType::String);

    CHECK(t.getName() == "students");
    CHECK(t.getColumnCount() == 2);
    CHECK(t.getColumnName(0) == "id");
    CHECK(t.getColumnType(0) == ColumnType::Int);

    Row r;
    r.addCell(new IntCell(1));
    r.addCell(new StringCell("Alice"));
    t.insertRow(r);

    CHECK(t.getRowCount() == 1);
    CHECK(t.getRow(0).getCell(0)->toString() == "1");
    CHECK(t.getRow(0).getCell(1)->toString() == "Alice");    
}
