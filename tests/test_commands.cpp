#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "../include/Command.hpp"
#include "../include/IntCell.hpp"
#include "../include/DoubleCell.hpp"
#include "../include/StringCell.hpp"
#include "../include/NullCell.hpp"
#include "../include/Table.hpp"
#include "../include/Database.hpp"
#include "../include/InsertCommand.hpp"
#include "../include/AddColumnCommand.hpp"
#include "../include/AggregateCommand.hpp"
#include "../include/InnerJoinCommand.hpp"



TEST_CASE("AddColumnCommand") {
    Database db;
    Table table("TestTable");
    table.addColumn("id", ColumnType::Int);
    db.addTable(table);

    AddColumnCommand cmd;
    
    SUBCASE("Add column to existing table") {
        CHECK_NOTHROW(cmd.execute({"TestTable", "name", "String"}, db));
        CHECK(db.getTableByName("TestTable").getColumnCount() == 2);
        CHECK(db.getTableByName("TestTable").getColumnType(1) == ColumnType::String);
        CHECK(db.getTableByName("TestTable").getColumnName(1) == "name");
    }
    
    SUBCASE("Add column to non-existing table") {
        CHECK_THROWS_AS(cmd.execute({"NonExistingTable", "age", "Int"}, db), std::invalid_argument);
    }
    
    SUBCASE("Add column with invalid type") {
        CHECK_THROWS_AS(cmd.execute({"TestTable", "height", "InvalidType"}, db), std::invalid_argument);
    }

    SUBCASE("Add column with duplicate name") {
        CHECK_THROWS_AS(cmd.execute({"TestTable", "id", "Int"}, db), std::invalid_argument); // Adding duplicate column
    }

}


TEST_CASE("AggregateCommand") {
    Database db;
    Table table("Numbers");
    table.addColumn("group", ColumnType::Int);
    table.addColumn("value", ColumnType::Double);

    // Добавяме редове
    {
        Row r1; r1.addCell(new IntCell(1)); r1.addCell(new DoubleCell(2.5)); table.insertRow(r1);
        Row r2; r2.addCell(new IntCell(1)); r2.addCell(new DoubleCell(3.5)); table.insertRow(r2);
        Row r3; r3.addCell(new IntCell(2)); r3.addCell(new DoubleCell(4.0)); table.insertRow(r3);
    }
    db.addTable(table);

    AggregateCommand cmd;

    SUBCASE("Sum for group 1") {
        CHECK_NOTHROW(cmd.execute({"Numbers", "0", "1", "1", "sum"}, db));
        // Очакваният резултат е 2.5 + 3.5 = 6.0 (провери на конзолата)
    }
    SUBCASE("Product for group 1") {
        CHECK_NOTHROW(cmd.execute({"Numbers", "0", "1", "1", "product"}, db));
        // Очакваният резултат е 2.5 * 3.5 = 8.75
    }
    SUBCASE("Minimum for group 1") {
        CHECK_NOTHROW(cmd.execute({"Numbers", "0", "1", "1", "minimum"}, db));
        // Очакваният резултат е 2.5
    }
    SUBCASE("Maximum for group 1") {
        CHECK_NOTHROW(cmd.execute({"Numbers", "0", "1", "1", "maximum"}, db));
        // Очакваният резултат е 3.5
    }
    SUBCASE("Sum for group 2") {
        CHECK_NOTHROW(cmd.execute({"Numbers", "0", "2", "1", "sum"}, db));
        // Очакваният резултат е 4.0
    }
    SUBCASE("No match returns message") {
        CHECK_NOTHROW(cmd.execute({"Numbers", "0", "999", "1", "sum"}, db));
        // Очаква се съобщение "No values found for aggregation"
    }
    SUBCASE("Invalid operation throws") {
        CHECK_THROWS_AS(cmd.execute({"Numbers", "0", "1", "1", "unknownop"}, db), std::invalid_argument);
    }
    SUBCASE("Invalid column index throws") {
        CHECK_THROWS_AS(cmd.execute({"Numbers", "5", "1", "1", "sum"}, db), std::invalid_argument);
    }
    SUBCASE("Non-numeric target column throws") {
        Table t2("T2");
        t2.addColumn("id", ColumnType::Int);
        t2.addColumn("name", ColumnType::String);
        Row r; r.addCell(new IntCell(1)); r.addCell(new StringCell("abc")); t2.insertRow(r);
        db.addTable(t2);
        CHECK_THROWS_AS(cmd.execute({"T2", "0", "1", "1", "sum"}, db), std::invalid_argument);
    }
}


TEST_CASE("InnerJoinCommand") {
    Database db;

    // Създаваме първа таблица
    Table t1("T1");
    t1.addColumn("id", ColumnType::Int);
    t1.addColumn("name", ColumnType::String);
    {
        Row r1; r1.addCell(new IntCell(1)); r1.addCell(new StringCell("Ivan")); t1.insertRow(r1);
        Row r2; r2.addCell(new IntCell(2)); r2.addCell(new StringCell("Maria")); t1.insertRow(r2);
        Row r3; r3.addCell(new IntCell(3)); r3.addCell(new StringCell("Petar")); t1.insertRow(r3);
    }
    db.addTable(t1);
    db.registerTableFile("T1", "t1.csv");

    // Създаваме втора таблица
    Table t2("T2");
    t2.addColumn("id", ColumnType::Int);
    t2.addColumn("grade", ColumnType::Int);
    {
        Row r1; r1.addCell(new IntCell(1)); r1.addCell(new IntCell(6)); t2.insertRow(r1);
        Row r2; r2.addCell(new IntCell(2)); r2.addCell(new IntCell(5)); t2.insertRow(r2);
        Row r3; r3.addCell(new IntCell(4)); r3.addCell(new IntCell(4)); t2.insertRow(r3);
    }
    db.addTable(t2);
    db.registerTableFile("T2", "t2.csv");

    InnerJoinCommand cmd;
    CHECK_NOTHROW(cmd.execute({"T1", "0", "T2", "0"}, db));

    // Проверка дали новата таблица съществува
    std::string joinedName = "T1_join_T2";
    CHECK(db.hasTable(joinedName));
    const Table& joined = db.getTableByName(joinedName);

    // Проверка на броя на колоните: 2 (от T1) + 1 (от T2, без join колоната)
    CHECK(joined.getColumnCount() == 3);

    // Проверка на броя на редовете: само тези с еднакво id (1 и 2)
    CHECK(joined.getRowCount() == 2);

    // Проверка на стойностите в първия ред
    CHECK(joined.getRow(0).getCell(0)->toString() == "1"); // id от T1
    CHECK(joined.getRow(0).getCell(1)->toString() == "Ivan"); // name от T1
    CHECK(joined.getRow(0).getCell(2)->toString() == "6"); // grade от T2

    // Проверка на стойностите във втория ред
    CHECK(joined.getRow(1).getCell(0)->toString() == "2");
    CHECK(joined.getRow(1).getCell(1)->toString() == "Maria");
    CHECK(joined.getRow(1).getCell(2)->toString() == "5");

    CHECK_THROWS_AS(cmd.execute({"T1", "0", "T100", "0"}, db), std::invalid_argument);
}


TEST_CASE("InsertCommand") {
    Database db;
    Table table("TestTable");
    table.addColumn("id", ColumnType::Int);
    db.addTable(table);
    //db.registerTableFile("TestTable", "test_table.txt");

    InsertCommand insertCmd;
    CHECK_NOTHROW(insertCmd.execute({"TestTable", "1"}, db));
    CHECK(db.getTableByName("TestTable").getRowCount() == 1);
}



