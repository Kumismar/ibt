target_sources(Parser PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp"
)

set_target_properties(Parser PROPERTIES 
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/logger.hpp"
)