target_sources(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/exception_base.cpp"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PUBLIC_HEADER "invalid_symbol.hpp"
    PUBLIC_HEADER "empty_stack.hpp"
)