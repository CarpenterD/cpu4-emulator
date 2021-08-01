cmake_minimum_required(VERSION 3.10)

project(cpu4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add files and executable
set(SRC_DIR src)
file(GLOB SOURCES ${SRC_DIR}/*.cpp)

add_executable(cpu4 ${SOURCES})
