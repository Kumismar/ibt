set(project_dir
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

file(GLOB sources 
    *.cpp
)

add_executable(Parser 
    ${sources}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${project_dir}/build)

target_compile_options(Parser PRIVATE
    -Wall
    -Wextra
    -std=c++20
)