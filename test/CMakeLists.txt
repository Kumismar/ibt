# Author: Ondřej Koumar
# Date: 2024-03-18

include(FetchContent)

set(project_dir
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

add_executable(ParserTest
    precedence_parser_tests.cpp
    predictive_parser_tests.cpp
)

target_include_directories(ParserTest PRIVATE 
    ${project_dir}/src/lex
    ${project_dir}/src/grammars
    ${project_dir}/src/parsers
    ${project_dir}/src/logger
    ${project_dir}/src/exceptions
    ${project_dir}/src/tables
    ${project_dir}/src/types
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${project_dir}/build)

target_link_libraries(ParserTest PRIVATE
    ParserLibrary GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ParserTest)