# @ Author: Ondřej Koumar
# @ Email: xkouma02@stud.fit.vutbr.cz
# @ Create Time: 2024-04-13 20:05



target_sources(ParserLibrary PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/nonterminal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/token.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stack_item.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/precedence_symbol.cpp
)

set_target_properties(ParserLibrary PROPERTIES
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/nonterminal.hpp
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/stack_item.hpp
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/token.hpp
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/precedence_symbol.hpp
)