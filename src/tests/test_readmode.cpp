#include <catch/catch.hpp>
#include <sstream>
#include "csvreader.h"

using namespace CsvReader;

TEST_CASE("Testing strict readmode with norm data", "[readmode]")
{
    std::string str = 
R"(10; qwerty; 3
11; look at me; 1
12; hello; 4
)";
    std::stringstream ss(str);

    Reader<int, std::string, int> reader;
    reader.setReadMode(ReadMode::Strict);
    reader.setFieldDelimiter(';');
    reader.setEndLine('\n');
    bool status = true;
    std::vector<Reader<int, std::string, int>::RowType> table;
    REQUIRE_NOTHROW(table = reader.read(ss, &status));
    REQUIRE(status == true);

    REQUIRE(table.size() == 3);
    
    CHECK(std::get<0>(table.at(0)) == 10);
    CHECK(std::get<0>(table.at(1)) == 11);
    CHECK(std::get<0>(table.at(2)) == 12);

    CHECK(std::get<1>(table.at(0)) == "qwerty");
    CHECK(std::get<1>(table.at(1)) == "look at me");
    CHECK(std::get<1>(table.at(2)) == "hello");

    CHECK(std::get<2>(table.at(0)) == 3);
    CHECK(std::get<2>(table.at(1)) == 1);
    CHECK(std::get<2>(table.at(2)) == 4);
}

TEST_CASE("Testing strict readmode with all fields empty", "[readmode][error]")
{
    std::string str = 
R"(10; qwerty
11; look at me
12; hello
)";
    std::stringstream ss(str);

    Reader<int, std::string, int> reader;
    reader.setReadMode(ReadMode::Strict);
    reader.setFieldDelimiter(';');
    reader.setEndLine('\n');
    bool status = true;

    REQUIRE_NOTHROW(reader.read(ss, &status));
    CHECK(status == false);
}

TEST_CASE("Testing strict readmode with part empty fields", "[readmode][error]")
{
    std::string str = 
R"(10; qwerty; 1
11; look at me
12; hello; 21
)";
    std::stringstream ss(str);

    Reader<int, std::string, int> reader;
    reader.setReadMode(ReadMode::Strict);
    reader.setFieldDelimiter(';');
    reader.setEndLine('\n');
    bool status = true;

    REQUIRE_NOTHROW(reader.read(ss, &status));
    CHECK(status == false);
}

TEST_CASE("Testing loose readmode with norm data", "[readmode]")
{
    std::string str = 
R"(10; qwerty; 3
11; look at me; 1
12; hello; 4
)";
    std::stringstream ss(str);

    Reader<int, std::string, int> reader;
    reader.setReadMode(ReadMode::Loose);
    reader.setFieldDelimiter(';');
    reader.setEndLine('\n');
    bool status = false;

    std::vector<Reader<int, std::string, int>::RowType> table;
    REQUIRE_NOTHROW(table = reader.read(ss, &status));
    REQUIRE(status == true);
    REQUIRE(table.size() == 3);
    
    CHECK(std::get<0>(table.at(0)) == 10);
    CHECK(std::get<0>(table.at(1)) == 11);
    CHECK(std::get<0>(table.at(2)) == 12);

    CHECK(std::get<1>(table.at(0)) == "qwerty");
    CHECK(std::get<1>(table.at(1)) == "look at me");
    CHECK(std::get<1>(table.at(2)) == "hello");

    CHECK(std::get<2>(table.at(0)) == 3);
    CHECK(std::get<2>(table.at(1)) == 1);
    CHECK(std::get<2>(table.at(2)) == 4);
}

TEST_CASE("Testing loose readmode with all fields empty", "[readmode][error]")
{
    std::string str = 
R"(10; qwerty
11; look at me
12; hello
)";
    std::stringstream ss(str);

    Reader<int, std::string, int> reader;
    reader.setReadMode(ReadMode::Loose);
    reader.setFieldDelimiter(';');
    reader.setEndLine('\n');
    bool status = false;

    std::vector<Reader<int, std::string, int>::RowType> table;
    REQUIRE_NOTHROW(table = reader.read(ss, &status));

    REQUIRE(status == true);
    REQUIRE(table.size() == 3);
    
    CHECK(std::get<0>(table.at(0)) == 10);
    CHECK(std::get<0>(table.at(1)) == 11);
    CHECK(std::get<0>(table.at(2)) == 12);

    CHECK(std::get<1>(table.at(0)) == "qwerty");
    CHECK(std::get<1>(table.at(1)) == "look at me");
    CHECK(std::get<1>(table.at(2)) == "hello");

    CHECK(std::get<2>(table.at(0)) == 0);
    CHECK(std::get<2>(table.at(1)) == 0);
    CHECK(std::get<2>(table.at(2)) == 0);
}

TEST_CASE("Testing loose readmode with empty fields", "[readmode][error]")
{
    std::string str = 
R"(10; qwerty; 1
11; look at me
12; hello; 21
)";
    std::stringstream ss(str);

    Reader<int, std::string, int> reader;
    reader.setReadMode(ReadMode::Loose);
    reader.setFieldDelimiter(';');
    reader.setEndLine('\n');
    bool status = false;

    std::vector<Reader<int, std::string, int>::RowType> table;
    REQUIRE_NOTHROW(table = reader.read(ss, &status));

    REQUIRE(status == true);
    REQUIRE(table.size() == 3);
    
    CHECK(std::get<0>(table.at(0)) == 10);
    CHECK(std::get<0>(table.at(1)) == 11);
    CHECK(std::get<0>(table.at(2)) == 12);

    CHECK(std::get<1>(table.at(0)) == "qwerty");
    CHECK(std::get<1>(table.at(1)) == "look at me");
    CHECK(std::get<1>(table.at(2)) == "hello");

    CHECK(std::get<2>(table.at(0)) == 1);
    CHECK(std::get<2>(table.at(1)) == 0);
    CHECK(std::get<2>(table.at(2)) == 21);
}

TEST_CASE("Testing loose readmode with multiple empty fields", "[readmode][error]")
{
    std::string str = 
R"(10.1; qwerty; 1
11.1; look at me;2;3
12.1; hello
)";
    std::stringstream ss(str);

    Reader<double, std::string, int, std::string> reader;
    reader.setReadMode(ReadMode::Loose);
    reader.setFieldDelimiter(';');
    reader.setEndLine('\n');
    bool status = false;

    std::vector<Reader<double, std::string, int, std::string>::RowType> table;
    REQUIRE_NOTHROW(table = reader.read(ss, &status));

    REQUIRE(status == true);
    REQUIRE(table.size() == 3);
    
    CHECK(std::get<0>(table.at(0)) == 10.1);
    CHECK(std::get<0>(table.at(1)) == 11.1);
    CHECK(std::get<0>(table.at(2)) == 12.1);

    CHECK(std::get<1>(table.at(0)) == "qwerty");
    CHECK(std::get<1>(table.at(1)) == "look at me");
    CHECK(std::get<1>(table.at(2)) == "hello");

    CHECK(std::get<2>(table.at(0)) == 1);
    CHECK(std::get<2>(table.at(1)) == 2);
    CHECK(std::get<2>(table.at(2)) == 0);

    CHECK(std::get<3>(table.at(0)) == "");
    CHECK(std::get<3>(table.at(1)) == "3");
    CHECK(std::get<3>(table.at(2)) == "");
}