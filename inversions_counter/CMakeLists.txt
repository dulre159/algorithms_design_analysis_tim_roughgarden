cmake_minimum_required(VERSION 3.30)
project(inversions_counter)

add_executable(inversions_counter)

target_compile_features(inversions_counter PRIVATE cxx_std_17)

target_sources(inversions_counter
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