#include <locale>
#include <optional>
#include "csvreader.h"

namespace CsvReader
{

template<>
std::string FromString<std::string>(const std::string &str) 
{
    return str;
}

class CommaPunct: public std::numpunct<char>
{
protected:
    char do_decimal_point() const {
        return ',';
    }
};

class DotPunct: public std::numpunct<char>
{
protected:
    char do_decimal_point() const {
        return '.';
    }
};

template<typename NumPunct>
std::optional<double> fromAnyDecPoint(const std::string &str) 
{
    std::istringstream stream(str);
    std::locale loc(std::locale(), new NumPunct());
    stream.imbue(loc);
    
    double result;
    stream >> result;

    if (!stream.eof() || stream.fail()) {
        return {};
    }

    return result;
}

template<>
double FromString<double>(const std::string &str) 
{
    if (auto result = fromAnyDecPoint<DotPunct>(str); result.has_value()) {
        return result.value();
    }
    
    if (auto result = fromAnyDecPoint<CommaPunct>(str); result.has_value()) {
        return result.value();
    }

    throw std::runtime_error("Bad cast to double in function FromString");
}

void simplify(std::string &str)
{
    str.erase(0, str.find_first_not_of("\t\n\v\f\r "));
    str.erase(str.find_last_not_of("\t\n\v\f\r ") + 1);
}

} //namespace CsvReader