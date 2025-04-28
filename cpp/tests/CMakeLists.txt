#-------------------------------------
#	for Google Test
#-------------------------------------

find_package(GTest REQUIRED)

file(GLOB_RECURSE TESTS test_*.cpp)
foreach(test ${TESTS})
    get_filename_component(target ${test} NAME_WE)
    add_executable(${target} ${test})
    target_link_libraries(${target} GTest::GTest GTest::Main ${PROJECT_NAME})
    target_include_directories(${target} PRIVATE ../lib/include)
    include(GoogleTest)
    gtest_add_tests(TARGET ${target})
endforeach()

# include(GoogleTest)

# add_executable(${PROJECT_NAME}-googletest ${TESTS})
# target_include_directories(${PROJECT_NAME}-googletest PRIVATE ../lib/include)
# target_link_libraries(${PROJECT_NAME}-googletest GTest::GTest GTest::Main ${PROJECT_NAME})

# gtest_add_tests(TARGET ${PROJECT_NAME}-googletest)


# # https://qiita.com/utkamioka/items/cacb1001bd2abf605b15
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   DOWNLOAD_EXTRACT_TIMESTAMP ON
#   GIT_REPOSITORY https://github.com/google/googletest.git
#   GIT_TAG        v1.16.0
# )
# if (WIN32)
# # For Windows: Prevent overriding the parent project's compiler/linker settings
#     set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# endif()
# FetchContent_MakeAvailable(googletest)

# file(GLOB_RECURSE TESTS test_*.cpp)

# add_executable(${PROJECT_NAME}-googletest ${TESTS})
# target_link_libraries(${PROJECT_NAME}-googletest gtest_main ${PROJECT_NAME})
# target_include_directories(${PROJECT_NAME}-googletest PRIVATE ../lib/include)
# include(GoogleTest)
# gtest_discover_tests(${PROJECT_NAME}-googletest)
# # add_test(NAME test COMMAND ${PROJECT_NAME}-googletest)
