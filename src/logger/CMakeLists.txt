target_sources(ParserLibrary PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp"
)

set_target_properties(ParserLibrary PROPERTIES 
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/logger.hpp"
)