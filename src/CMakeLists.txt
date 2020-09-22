add_subdirectory(parser)
add_subdirectory(model)
add_subdirectory(nodes)
add_subdirectory(compiler)

add_executable(jet main.cpp)
target_link_libraries(jet PUBLIC compiler)
