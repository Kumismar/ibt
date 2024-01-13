include(FetchContent)

set(project_dir
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set(obj_src_dir
    ${project_dir}/build/src/CMakeFiles/Parser.dir
)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

file(GLOB test_sources 
    *.cpp
)

add_executable(ParserTest   
    ${test_sources}
)

target_link_libraries(ParserTest
    ${obj_src_dir}/bruh.cpp.o
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ParserTest)