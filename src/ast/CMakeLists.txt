target_include_directories(ParserLibrary PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/expression
    ${CMAKE_CURRENT_SOURCE_DIR}/statements
)

add_subdirectory(expression)
add_subdirectory(statements)