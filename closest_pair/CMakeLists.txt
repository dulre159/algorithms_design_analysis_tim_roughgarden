cmake_minimum_required(VERSION 3.30)

project(closest_pair)

add_executable(closest_pair)

target_compile_features(closest_pair PRIVATE cxx_std_17)

target_sources(closest_pair
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