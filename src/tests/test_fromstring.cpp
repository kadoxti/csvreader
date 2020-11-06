#include <catch/catch.hpp>
#include <sstream>
#include "csvreader.h"

using namespace CsvReader;

TEST_CASE("Testing string to string", "[strings]")
{
    CHECK(FromString<std::string>("12") == "12");
    CHECK(FromString<std::string>("0") == "0");
    CHECK(FromString<std::string>("-123467890") == "-123467890");
    CHECK(FromString<std::string>("") == "");
    CHECK(FromString<std::string>("qwerty") == "qwerty");
    CHECK(FromString<std::string>(" qwe\r\trty") == " qwe\r\trty");
    CHECK(FromString<std::string>("\n") == "\n");
}

TEST_CASE("Testing string to int", "[strings]")
{
    CHECK(FromString<int>("12") == 12);
    CHECK(FromString<int>("0") == 0);
    CHECK(FromString<int>("-123467890") == -123467890);

    CHECK_THROWS(FromString<int>("12.4"));
    CHECK_THROWS(FromString<int>("12,4"));
    CHECK_THROWS(FromString<int>(" "));
    CHECK_THROWS(FromString<int>("qwerty"));
    CHECK_THROWS(FromString<int>("10qwerty"));
    CHECK_THROWS(FromString<int>("q"));
    CHECK_THROWS(FromString<int>("\n"));
}

TEST_CASE("Testing string to bool", "[strings]")
{
    CHECK(FromString<bool>("1") == true);
    CHECK(FromString<bool>("0") == false);
    
    CHECK_THROWS(FromString<bool>("10"));
    CHECK_THROWS(FromString<bool>("-123467890"));
    CHECK_THROWS(FromString<bool>(" "));
    CHECK_THROWS(FromString<bool>("qwerty"));
    CHECK_THROWS(FromString<bool>("q"));
    CHECK_THROWS(FromString<bool>("\n"));
}

TEST_CASE("Testing string to size_t", "[strings]")
{
    CHECK(FromString<size_t>("12") == 12u);
    CHECK(FromString<size_t>("0") == 0u);
    CHECK(FromString<size_t>("-123467890") == -123467890u);

    CHECK_THROWS(FromString<size_t>("12.4"));
    CHECK_THROWS(FromString<size_t>("12,4"));
    CHECK_THROWS(FromString<size_t>(" "));
    CHECK_THROWS(FromString<size_t>("qwerty"));
    CHECK_THROWS(FromString<size_t>("q"));
    CHECK_THROWS(FromString<size_t>("\n"));
}

TEST_CASE("Testing string to double", "[strings]")
{
    CHECK(FromString<double>("12") == 12.0);
    CHECK(FromString<double>("0") == 0.0);
    CHECK(FromString<double>("0.0") == 0.0);
    CHECK(FromString<double>("-12346,123") == -12346.123);
    CHECK(FromString<double>("12.435611") == 12.435611);
    CHECK(FromString<double>("-12,498722") == -12.498722);

    CHECK_THROWS(FromString<double>(" "));
    CHECK_THROWS(FromString<double>("qwerty"));
    CHECK_THROWS(FromString<double>("q"));
    CHECK_THROWS(FromString<double>("\n"));
    CHECK_THROWS(FromString<double>("10qwerty"));
}