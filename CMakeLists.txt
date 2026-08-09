cmake_minimum_required(VERSION 4.3)
project(multi_threding)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET pgcppmt)
add_executable(${TARGET})
target_sources(
        ${TARGET}

        PRIVATE
        main.cpp
)
