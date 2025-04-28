cmake_minimum_required(VERSION 3.12)

project(MeasureTime
    VERSION 1.0
    DESCRIPTION "Library to measure time, for C++"
    LANGUAGES CXX
    )

enable_testing()

add_subdirectory(lib)
add_subdirectory(tests)