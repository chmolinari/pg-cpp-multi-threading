cmake_minimum_required(VERSION 4.3)
project(multi_threading)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_DEBUG_POSTFIX d)

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

