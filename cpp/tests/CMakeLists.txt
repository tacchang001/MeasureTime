#-------------------------------------
#	for Google Test
#-------------------------------------

# https://siuncyclone.hatenablog.com/entry/2018/07/21/194629
set(CMAKE_CXX_FLAGS "-static -lstdc++ -lgcc -lwinpthread")

file(GLOB_RECURSE TESTS test_*.cpp)

# https://qiita.com/utkamioka/items/cacb1001bd2abf605b15
include(FetchContent)
FetchContent_Declare(
  googletest
  DOWNLOAD_EXTRACT_TIMESTAMP ON
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.1
)
if (WIN32)
# For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TESTS test_*.cpp)

add_executable(${PROJECT_NAME}-googletest ${TESTS})
target_link_libraries(${PROJECT_NAME}-googletest gtest_main ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}-googletest PRIVATE ../lib/include)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-googletest)
# add_test(NAME test COMMAND ${PROJECT_NAME}-googletest)
