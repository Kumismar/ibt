target_sources(Parser PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/ll_table.cpp"
)

set_target_properties(Parser PROPERTIES 
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/ll_table.hpp"
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/table_index.hpp"
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/precedence_table.hpp"
)