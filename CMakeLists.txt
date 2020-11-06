cmake_minimum_required(VERSION 3.14)

project (csvreader LANGUAGES CXX VERSION 1.0.0)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED On)

include_directories(
    "${PROJECT_SOURCE_DIR}/include"

    )

set (includes
    include/csvreader.h
)

set(sources
    src/csvreader/csvreader.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin/release)

add_library(${PROJECT_NAME} SHARED ${sources} ${includes})


set(test_sources
    src/tests/test_main.cpp
    src/tests/test_all_exists.cpp
    src/tests/test_defaults.cpp
    src/tests/test_string_manipulation.cpp
    src/tests/test_readmode.cpp
    src/tests/test_fromstring.cpp
    src/tests/test_error_not_exception.cpp
    src/tests/test_any_field_delimiter.cpp
    src/tests/test_any_linebreak.cpp
)

add_executable(${PROJECT_NAME}_test ${sources} ${includes} include/catch/catch.hpp ${test_sources})