# Author: Ondřej Koumar
# Date: 2024-03-18

target_sources(ParserLibrary PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/exception_base.cpp"
)

set_target_properties(ParserLibrary PROPERTIES
    PUBLIC_HEADER "internal_error.hpp"
    PUBLIC_HEADER "syntax_error.hpp"
    PUBLIC_HEADER "analysis_success.hpp"
    PUBLIC_HEADER "lexical_error.hpp"
)