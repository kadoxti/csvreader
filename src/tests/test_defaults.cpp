#include <catch/catch.hpp>
#include <sstream>
#include "csvreader.h"

using namespace CsvReader;

TEST_CASE("Testing default field delimiter for Reader", "[defaults]")
{
        std::string str = 
R"(10,32; qwerty
11,67; look at me
-12,561479; hello
)";
    std::stringstream ss(str);

    Reader<double, std::string> reader;
    reader.setReadMode(ReadMode::Strict);

    CHECK(reader.fieldDelimiter() == ';');

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

TEST_CASE("Testing default line break for Reader", "[defaults]")
{
    std::string str = "10,32; qwerty\n11,67; look at me\n-12,561479; hello";
    std::stringstream ss(str);

    Reader<double, std::string> reader;
    reader.setReadMode(ReadMode::Strict);

    CHECK(reader.endLine() == '\n');

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

TEST_CASE("Testing default readmode for Reader", "[defaults]")
{
        std::string str = 
R"(10,32; qwerty
11,67;
-12,561479; hello
)";
    std::stringstream ss(str);

    Reader<double, std::string> reader;
    REQUIRE(reader.readMode() == ReadMode::Loose);

    bool status = false;
    auto table = reader.read(ss, &status);
    
    REQUIRE(status == true);
    REQUIRE(table.size() == 3);

    CHECK(std::get<0>(table.at(0)) == 10.32);
    CHECK(std::get<0>(table.at(1)) == 11.67);
    CHECK(std::get<0>(table.at(2)) == -12.561479);

    CHECK(std::get<1>(table.at(0)) == "qwerty");
    CHECK(std::get<1>(table.at(1)) == "");
    CHECK(std::get<1>(table.at(2)) == "hello");
}