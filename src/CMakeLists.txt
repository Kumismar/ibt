set(project_dir ${CMAKE_CURRENT_SOURCE_DIR}/..)

file(GLOB sources 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file(GLOB_RECURSE headers 
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/*.hpp
)

add_executable(Parser 
    ${sources}
)

target_include_directories(Parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${project_dir}/build)

target_compile_options(Parser PRIVATE
    -Wall
    -Wextra
    -std=c++20
)