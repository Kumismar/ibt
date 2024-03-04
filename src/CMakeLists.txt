set(project_dir ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_library(ParserLibrary)

add_executable(Parser 
    main.cpp
)

target_link_libraries(Parser
    ParserLibrary
)

target_include_directories(ParserLibrary PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/lex
    ${CMAKE_CURRENT_SOURCE_DIR}/grammars
    ${CMAKE_CURRENT_SOURCE_DIR}/types
    ${CMAKE_CURRENT_SOURCE_DIR}/tables
    ${CMAKE_CURRENT_SOURCE_DIR}/parsers
    ${CMAKE_CURRENT_SOURCE_DIR}/exceptions
    ${CMAKE_CURRENT_SOURCE_DIR}/exceptions
    ${CMAKE_CURRENT_SOURCE_DIR}/logger
)

target_include_directories(Parser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/lex
    ${CMAKE_CURRENT_SOURCE_DIR}/grammars
    ${CMAKE_CURRENT_SOURCE_DIR}/types
    ${CMAKE_CURRENT_SOURCE_DIR}/tables
    ${CMAKE_CURRENT_SOURCE_DIR}/parsers
    ${CMAKE_CURRENT_SOURCE_DIR}/exceptions
    ${CMAKE_CURRENT_SOURCE_DIR}/exceptions
    ${CMAKE_CURRENT_SOURCE_DIR}/logger
)

add_subdirectory(lex)
add_subdirectory(grammars)
add_subdirectory(parsers)
add_subdirectory(tables)
add_subdirectory(types)
add_subdirectory(exceptions)
add_subdirectory(logger)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${project_dir}/build)

set_target_properties(ParserLibrary PROPERTIES
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/aux.hpp"
)

target_compile_options(ParserLibrary PRIVATE
    -Wall
    -Wextra
    -std=c++20
)

target_compile_options(Parser PRIVATE
    -Wall
    -Wextra
    -std=c++20
)