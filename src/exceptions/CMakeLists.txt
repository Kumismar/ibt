# @ Author: Ondřej Koumar
# @ Email: xkouma02@stud.fit.vutbr.cz
# @ Create Time: 2024-03-18 19:12
# @ Modified time: 2024-04-07 16:40

target_sources(ParserLibrary PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/exception_base.cpp"
)

set_target_properties(ParserLibrary PROPERTIES
    PUBLIC_HEADER "internal_error.hpp"
    PUBLIC_HEADER "syntax_error.hpp"
    PUBLIC_HEADER "analysis_success.hpp"
    PUBLIC_HEADER "lexical_error.hpp"
)