cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MeasureTime
    VERSION 1.0
    DESCRIPTION "Library to measure time, for C++"
    LANGUAGES CXX
    )

enable_testing()

# https://github.com/grpc/grpc/issues/6367
# 効かなかった
set(CMAKE_CXX_FLAGS "-mwin32 -D_WIN32_WINNT=0x600")

add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(example)