# Author: Ondřej Koumar
# Date: 2024-03-18

target_sources(ParserLibrary PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp"
)

set_target_properties(ParserLibrary PROPERTIES 
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/logger.hpp"
)