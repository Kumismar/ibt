target_sources(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/grammar_1.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/grammar_2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/grammar_3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/grammar_4.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/grammar_5.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/grammar_6.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/grammar_factory.cpp"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/grammar.hpp"
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/grammar_1.hpp"
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/grammar_2.hpp"
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/grammar_3.hpp"
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/grammar_4.hpp"
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/grammar_5.hpp"
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/grammar_6.hpp"
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/grammar_factory.hpp"
)