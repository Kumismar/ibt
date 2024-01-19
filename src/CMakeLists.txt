set(project_dir ${CMAKE_CURRENT_SOURCE_DIR}/..)

file(GLOB sources 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(Parser 
    ${sources}
    ${headers}
)

target_include_directories(Parser PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/grammars
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/types
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/tables
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${project_dir}/build)

target_compile_options(Parser PRIVATE
    -Wall
    -Wextra
    -std=c++20
)