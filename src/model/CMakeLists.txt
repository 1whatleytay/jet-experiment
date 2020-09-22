add_library(model STATIC
    include/model/model.h

    model.cpp)

target_include_directories(model PUBLIC include)