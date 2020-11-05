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
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin/release)

add_library(${PROJECT_NAME} SHARED ${sources} ${includes})