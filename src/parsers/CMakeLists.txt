target_sources(Parser PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/predictive.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/precedence.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp"
)

set_target_properties(Parser PROPERTIES 
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/predictive.hpp"
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/precedence.hpp"
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/parser.hpp"
)