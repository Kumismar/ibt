target_sources(Parser PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/pushdown.cpp"
)

set_target_properties(Parser PROPERTIES 
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/pushdown.hpp"
)