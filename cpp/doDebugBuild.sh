#!/bin/sh

if [ -d "build" ]; then
    rm -rf build
fi

cmake -S . -B build -D CMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" -D CMAKE_VERBOSE_MAKEFILE=ON -D gtest_disable_pthreads=ON -D CMAKE_POLICY_VERSION_MINIMUM=3.5
cmake --build build
