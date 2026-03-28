cmake_minimum_required(VERSION 3.30)

project(sorting)

add_executable(sorting)

target_compile_features(sorting PRIVATE cxx_std_17)

target_sources(sorting
PRIVATE
    main.cpp
    ../commons/commons.cpp
    ../commons/vector_utils.cpp
PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
        .
        ../commons
    FILES
        sorting.h
        sorting.tpp
        ../commons/commons.h
        ../commons/vector_utils.h
)