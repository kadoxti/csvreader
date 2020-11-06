#include <catch/catch.hpp>
#include <sstream>
#include "csvreader.h"

using namespace CsvReader;

TEST_CASE("Testing string simplification", "[strings]")
{
    std::string str = "  \n\t\v\f\r qwerty\t\r \v  \n\f";
    simplify(str);
    CHECK(str == "qwerty");
}

TEST_CASE("Testing string {int} simplification", "[strings]")
{
    std::string str = "  \n\t\v\f\r 123\t\r \v  \n\f";
    simplify(str);
    CHECK(str == "123");
}

TEST_CASE("Testing string {double} simplification", "[strings]")
{
    std::string str = "  \n\t\v\f\r 123.123\t\r \v  \n\f";
    simplify(str);
    CHECK(str == "123.123");
}