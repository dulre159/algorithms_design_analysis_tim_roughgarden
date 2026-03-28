cmake_minimum_required(VERSION 3.30)

project(integers_multiplication)

add_executable(integers_multiplication)

target_compile_features(integers_multiplication PRIVATE cxx_std_17)

target_sources(integers_multiplication
PRIVATE
    main.cpp
    ../commons/commons.cpp
    ../commons/vector_utils.cpp
PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
        ../commons
    FILES
        ../commons/commons.h
        ../commons/vector_utils.h
)