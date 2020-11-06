#include <catch/catch.hpp>
#include <sstream>
#include "csvreader.h"

using namespace CsvReader;

TEST_CASE("Testing simple csv parsing {int, string}", "[main]")
{
    std::string str = 
R"(10; qwerty
11; look at me
12; hello
)";
    std::stringstream ss(str);

    Reader<int, std::string> reader;
    reader.setReadMode(ReadMode::Strict);
    reader.setFieldDelimiter(';');
    reader.setEndLine('\n');
    std::vector<std::tuple<int, std::string>> table = reader.read(ss);

    REQUIRE(table.size() == 3);
    
    CHECK(std::get<0>(table.at(0)) == 10);
    CHECK(std::get<0>(table.at(1)) == 11);
    CHECK(std::get<0>(table.at(2)) == 12);

    CHECK(std::get<1>(table.at(0)) == "qwerty");
    CHECK(std::get<1>(table.at(1)) == "look at me");
    CHECK(std::get<1>(table.at(2)) == "hello");
}

TEST_CASE("Testing simple csv parsing {int, double, int}", "[main]")
{
    std::string str = 
R"(10; 13.2; 10
11;14.5 ; 11
12; 67.3; 12
12; 67.3; 12
)";
    std::stringstream ss(str);

    Reader<int, double, int> reader;
    reader.setReadMode(ReadMode::Strict);
    reader.setFieldDelimiter(';');
    reader.setEndLine('\n');
    std::vector<std::tuple<int, double, int>> table = reader.read(ss);

    REQUIRE(table.size() == 4);
    
    CHECK(std::get<0>(table.at(0)) == 10);
    CHECK(std::get<0>(table.at(1)) == 11);
    CHECK(std::get<0>(table.at(2)) == 12);
    CHECK(std::get<0>(table.at(2)) == 12);

    CHECK(std::get<1>(table.at(0)) == 13.2);
    CHECK(std::get<1>(table.at(1)) == 14.5);
    CHECK(std::get<1>(table.at(2)) == 67.3);
    CHECK(std::get<1>(table.at(2)) == 67.3);

    CHECK(std::get<2>(table.at(0)) == 10);
    CHECK(std::get<2>(table.at(1)) == 11);
    CHECK(std::get<2>(table.at(2)) == 12);
    CHECK(std::get<2>(table.at(2)) == 12);
}