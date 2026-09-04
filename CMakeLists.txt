cmake_minimum_required(VERSION 4.3)
project(multi_threading)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_DEBUG_POSTFIX d)

find_package(Boost CONFIG REQUIRED COMPONENTS log)

set(BUILD_NAME pgcppmt)
add_executable(${BUILD_NAME})
target_sources(
        ${BUILD_NAME}

        PUBLIC
        FILE_SET ${BUILD_NAME}_headers
        TYPE HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES
        include/log_definitions.hpp

        PRIVATE
        src/main.cpp
        src/log_definitions.cpp
)
target_link_libraries(
        ${BUILD_NAME}

        PRIVATE
        Boost::log
)

