set(project_dir ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(Parser 
    main.cpp
)

target_include_directories(Parser PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/grammars
    ${CMAKE_CURRENT_SOURCE_DIR}/types
    ${CMAKE_CURRENT_SOURCE_DIR}/tables
    ${CMAKE_CURRENT_SOURCE_DIR}/pushdowns
)

add_subdirectory(grammars)
add_subdirectory(pushdowns)
add_subdirectory(tables)
add_subdirectory(types)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${project_dir}/build)

target_compile_options(Parser PRIVATE
    -Wall
    -Wextra
    -std=c++20
)