#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "../include/Table.hpp"
#include "../include/Database.hpp"

TEST_CASE("Database basic operations") {
    Database db;

    Table t1("grades");
    t1.addColumn("subject", ColumnType::String);
    db.addTable(t1);

    CHECK(db.hasTable("grades"));
    CHECK_NOTHROW(db.getTableByName("grades"));
    CHECK_THROWS_AS(db.getTableByName("nonexistent"), std::invalid_argument);
}

TEST_CASE("Database rename operation") {
    Database db;

    Table t1("grades");
    t1.addColumn("subject", ColumnType::String);
    t1.addColumn("score", ColumnType::Int);
    db.addTable(t1);

    Table t2("students");
    t2.addColumn("name", ColumnType::String);
    t2.addColumn("age", ColumnType::Int);
    db.addTable(t2);

    CHECK(db.listTableNames().size() == 2);
    CHECK(db.listTableNames()[0] == "grades");
    CHECK(db.listTableNames()[1] == "students");

    db.renameTable("grades", "course_grades");
    CHECK(db.hasTable("course_grades"));
    CHECK_FALSE(db.hasTable("grades"));
}