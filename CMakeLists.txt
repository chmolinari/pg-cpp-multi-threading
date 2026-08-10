cmake_minimum_required(VERSION 4.3)
project(multi_threding)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(runtime_dependencies)

find_package(Boost REQUIRED COMPONENTS log)

set(TARGET pgcppmt)
add_executable(${TARGET})
target_sources(
        ${TARGET}

        PRIVATE
        main.cpp
)
target_link_libraries(
        ${TARGET}

        PRIVATE
        Boost::log
)
add_runtime_dependencies_target(${TARGET})
