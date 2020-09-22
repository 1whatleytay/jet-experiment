add_library(nodes STATIC
    include/nodes/chip.h
    include/nodes/code.h
    include/nodes/root.h
    include/nodes/constant.h
    include/nodes/constexpr.h
    include/nodes/declare.h
    include/nodes/expression.h
    include/nodes/if.h
    include/nodes/make.h
    include/nodes/node.h
    include/nodes/operator.h
    include/nodes/output.h
    include/nodes/repeat.h
    include/nodes/show.h
    include/nodes/utils.h
    include/nodes/wire.h

    chip.cpp
    code.cpp
    root.cpp
    constant.cpp
    constexpr.cpp
    declare.cpp
    expression.cpp
    if.cpp
    make.cpp
    node.cpp
    output.cpp
    repeat.cpp
    show.cpp
    utils.cpp
    wire.cpp)

target_include_directories(nodes PUBLIC include)
target_link_libraries(nodes PUBLIC parser model)
