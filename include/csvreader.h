#pragma once

#include <vector>
#include <tuple>
#include <mutex>
#include <string>
#include <exception>
#include <sstream>

#include <iostream>

namespace CsvReader
{

enum class ReadMode 
{
    Loose, // Успешное чтение, даже в случае некорректного количества полей
    Strict // Требовать как минимум заданное количество полей
};

class StrictReadViolation: public std::runtime_error
{
public:
    StrictReadViolation(const std::string &str): std::runtime_error(str){}
    StrictReadViolation(const char *str): std::runtime_error(str){}
    StrictReadViolation(): std::runtime_error("Csv read error due to Strict read mode") {};
};

template<typename T>
T FromString(const std::string &str) 
{
    T result;
    std::istringstream stream(str);
    stream >> result;

    if (stream.fail() || !stream.eof()) {
        throw std::runtime_error("Bad cast in function FromString");
    }

    return result;
}

template<>
std::string FromString<std::string>(const std::string &str);

template<>
double FromString<double>(const std::string &str);

void simplify(std::string &str);

template <typename ...Types>
class LineParser
{
public:
    std::tuple<Types...> parse(std::istream &stream, ReadMode readMode, char fieldDelimiter) const;
};

template<typename ...Types>
class Reader
{

public:
    using RowType = typename std::tuple<Types...>;

    void setReadMode(ReadMode mode) {
        std::lock_guard g(_mutex);
        _readMode = mode;
    }

    ReadMode readMode() const {
        return _readMode;
    }

    void setFieldDelimiter(char delimiter) {
        std::lock_guard g(_mutex);
        _fieldDelimiter = delimiter;
    }

    char fieldDelimiter() const {
        return _fieldDelimiter;
    }

    void setEndLine(char delimiter) {
        std::lock_guard g(_mutex);
        _endLine = delimiter;
    }

    char endLine() {
        return _endLine;
    }

    std::vector<std::tuple<Types...>> read(std::istream &stream, bool *status = nullptr) const try {
        std::vector<std::tuple<Types...>> result;

        for (std::string bufLine; std::getline(stream, bufLine, _endLine); ) {
            std::istringstream fieldStream(bufLine);
            auto valueTuple = LineParser<Types...>().parse(fieldStream, _readMode, _fieldDelimiter);
            result.push_back(std::move(valueTuple));
        }

        if (status) {
            *status = true;
        }

        return result;
    } catch (...) {
        if (status) {
            *status = false;
        }
        return {};
    }

private:
    ReadMode _readMode = ReadMode::Loose;
    mutable std::mutex _mutex;
    char _fieldDelimiter = ';';
    char _endLine = '\n';

    std::tuple<Types...> parseLine (std::istream &stream) const;
};



template <typename T>
class LineParser <T>
{
public:
    std::tuple<T> parse(std::istream &stream, ReadMode readMode, char fieldDelimiter) const {
        std::string bufField;
        std::getline(stream, bufField, fieldDelimiter);
        if (bufField.empty() && readMode == ReadMode::Strict) {
            throw StrictReadViolation();
        } else if (bufField.empty() && readMode == ReadMode::Loose) {
            return {T()};
        }
        
        simplify(bufField);

        return {FromString<T>(bufField)};
    }
};

template <typename T, typename ...Types>
class LineParser <T, Types...>
{
public:
    std::tuple<T, Types...> parse(std::istream &stream, ReadMode readMode, char fieldDelimiter) const {
        auto t1 = LineParser<T>().parse(stream, readMode, fieldDelimiter);
        auto t2 = LineParser<Types...>().parse(stream, readMode, fieldDelimiter);

        return std::tuple_cat(t1, t2);
    }
};

} //namespace CsvReader