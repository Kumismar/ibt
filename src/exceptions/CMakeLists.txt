target_sources(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/exception_base.cpp"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PUBLIC_HEADER "internal_error.hpp"
    PUBLIC_HEADER "syntax_error.hpp"
)