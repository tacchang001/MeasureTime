
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (LIBNAME MeasureTime)

add_library(${LIBNAME}
    STATIC
        src/StopWatch.cpp
        src/AutoCloseable.cpp
        src/MeasurementReport.cpp
        src/MeasurementResult.cpp
        )

target_include_directories(${LIBNAME}
    PRIVATE
        include
        )

target_link_libraries(${LIBNAME}
    )

add_definitions(-DDEBUG)

target_link_options(${LIBNAME}
    PRIVATE 
#        "-Wl,--no-undefined"
#        "-Wl,-verbose"
        )
