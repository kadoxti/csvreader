#include <catch/catch.hpp>
#include <sstream>
#include "csvreader.h"

using namespace CsvReader;

TEST_CASE("Testing \\n as line break", "[delimiter]")
{
    std::string str = "10,32; qwerty\n11,67; look at me\n-12,561479; hello";
    std::stringstream ss(str);

    Reader<double, std::string> reader;
    reader.setReadMode(ReadMode::Strict);
    reader.setEndLine('\n');

    bool status = false;
    auto table = reader.read(ss, &status);
    
    REQUIRE(status == true);
    REQUIRE(table.size() == 3);

    CHECK(std::get<0>(table.at(0)) == 10.32);
    CHECK(std::get<0>(table.at(1)) == 11.67);
    CHECK(std::get<0>(table.at(2)) == -12.561479);

    CHECK(std::get<1>(table.at(0)) == "qwerty");
    CHECK(std::get<1>(table.at(1)) == "look at me");
    CHECK(std::get<1>(table.at(2)) == "hello");
}

TEST_CASE("Testing b as line break", "[delimiter]")
{
    std::string str = "10,32; qwertyb11,67; look at meb-12,561479; hello";
    std::stringstream ss(str);

    Reader<double, std::string> reader;
    reader.setReadMode(ReadMode::Strict);
    reader.setEndLine('b');

    bool status = false;
    auto table = reader.read(ss, &status);
    
    REQUIRE(status == true);
    REQUIRE(table.size() == 3);

    CHECK(std::get<0>(table.at(0)) == 10.32);
    CHECK(std::get<0>(table.at(1)) == 11.67);
    CHECK(std::get<0>(table.at(2)) == -12.561479);

    CHECK(std::get<1>(table.at(0)) == "qwerty");
    CHECK(std::get<1>(table.at(1)) == "look at me");
    CHECK(std::get<1>(table.at(2)) == "hello");
}