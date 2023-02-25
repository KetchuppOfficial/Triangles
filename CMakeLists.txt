cmake_minimum_required(VERSION 3.8)

project(HW3D
        LANGUAGES CXX)

if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source build is forbidden")
endif()

find_package(GTest REQUIRED)
enable_testing()

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/../)
set(INCLUDE_DIR ${PROJECT_BINARY_DIR}/../include)

add_subdirectory(test)
