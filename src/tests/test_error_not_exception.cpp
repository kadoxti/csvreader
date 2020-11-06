#include <catch/catch.hpp>
#include <sstream>
#include "csvreader.h"

using namespace CsvReader;

TEST_CASE("Testing bad fields", "[error]")
{
    std::string str = 
R"(10; qwerty
11; look at me
12; 22
)";
    std::stringstream ss(str);

    Reader<int, int> reader;
    reader.setReadMode(ReadMode::Strict);
    reader.setFieldDelimiter(';');
    reader.setEndLine('\n');

    bool status = true;
    REQUIRE_NOTHROW(reader.read(ss, &status));
    CHECK(status == false);
}

TEST_CASE("Testing bad fields 2", "[error]")
{
    std::string str = 
R"(10; 10
11; 22,1
12; qwer12
)";
    std::stringstream ss(str);

    Reader<int, int> reader;
    reader.setReadMode(ReadMode::Strict);
    reader.setFieldDelimiter(';');
    reader.setEndLine('\n');

    bool status = true;
    REQUIRE_NOTHROW(reader.read(ss, &status));
    CHECK(status == false);
}

TEST_CASE("Testing strict readmode with all fields empty (duplicate from test_readmode)", "[readmode][error]")
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