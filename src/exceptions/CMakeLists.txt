# @ Author: Ondřej Koumar
# @ Email: xkouma02@stud.fit.vutbr.cz
# @ Create Time: 2024-03-18 19:12

target_sources(ParserLibrary PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/exception_base.cpp
)

set_target_properties(ParserLibrary PROPERTIES
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/internal_error.hpp
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/syntax_error.hpp
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/analysis_success.hpp
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/lexical_error.hpp
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/function_parsed.hpp
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/help.hpp
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/invalid_cmd_arguments.hpp
)