file(GLOB_RECURSE tmp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

set(headers ${headers} ${tmp} PARENT_SCOPE)