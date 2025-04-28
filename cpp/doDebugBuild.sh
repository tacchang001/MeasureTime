#!/bin/sh

if [ -d "build" ]; then
    rm -rf build
fi

cmake -S . -B build -D CMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" -D CMAKE_VERBOSE_MAKEFILE=ON -D gtest_disable_pthreads=ON
cmake --build build
