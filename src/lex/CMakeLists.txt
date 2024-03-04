find_package(FLEX REQUIRED)

FLEX_TARGET(ParserLibrary "${CMAKE_CURRENT_SOURCE_DIR}/lex.l" "${CMAKE_CURRENT_SOURCE_DIR}/lex.yy.cc"
DEFINES_FILE "${CMAKE_CURRENT_SOURCE_DIR}/lex.yy.h")

target_sources(ParserLibrary PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/lex.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lex.yy.cc"
)

set_target_properties(ParserLibrary PROPERTIES 
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/lex.hpp"
)