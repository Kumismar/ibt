# Author: Ondřej Koumar
# Date: 2024-03-18

target_sources(ParserLibrary PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/ll_table.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/precedence_table.cpp"
)

set_target_properties(ParserLibrary PROPERTIES 
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/ll_table.hpp"
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/table_index.hpp"
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/precedence_table.hpp"
)