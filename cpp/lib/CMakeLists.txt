
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} 
    STATIC
        src/StopWatch.cpp
        src/AutoCloseable.cpp
        src/MeasurementReport.cpp
        src/MeasurementResult.cpp
        )

target_include_directories(${PROJECT_NAME}
    PRIVATE
        include
        )

target_link_libraries(${PROJECT_NAME} 
    )

add_definitions(-DDEBUG)

target_link_options(${PROJECT_NAME}
    PRIVATE 
#        "-Wl,--no-undefined"
#        "-Wl,-verbose"
        )
