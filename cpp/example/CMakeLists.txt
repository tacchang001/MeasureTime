
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(example 
        main.cpp
        )

target_include_directories(example
    PRIVATE
        ../lib/include
        )

target_link_libraries(example
    ${PROJECT_NAME} 
    )

set(CMAKE_CXX_FLAGS "-static -lstdc++ -lgcc -lwinpthread")
add_definitions(-DDEBUG)

target_link_options(${PROJECT_NAME}
    PRIVATE 
#        "-Wl,--no-undefined"
#        "-Wl,-verbose"
        )
