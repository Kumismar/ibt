# Author: Ondřej Koumar
# Date: 2024-03-18

target_sources(ParserLibrary PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/predictive.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/precedence.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp"
)

set_target_properties(ParserLibrary PROPERTIES 
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/predictive.hpp"
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/precedence.hpp"
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/parser.hpp"
)