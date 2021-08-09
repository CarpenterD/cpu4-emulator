cmake_minimum_required(VERSION 3.10)

project(cpu4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add files and executable
set(SRC_DIR src)
file(GLOB CPU_SOURCES ${SRC_DIR}/cpu/*.cpp)
file(GLOB ASM_SOURCES ${SRC_DIR}/asm/*.cpp)

add_executable(cpu4 ${CPU_SOURCES})
add_executable(asm4 ${ASM_SOURCES})

target_include_directories(asm4  PRIVATE ${SRC_DIR})