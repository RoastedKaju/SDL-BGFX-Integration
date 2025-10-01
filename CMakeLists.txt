cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name
project(SDL-Integration)

# Architecture
set(OSBitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBitness 64)
endif()

# Make executable
add_executable(${PROJECT_NAME} "src/main.cpp")

add_subdirectory(extern/SDL)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

add_subdirectory(extern/bgfx-cmake)
target_link_libraries(${PROJECT_NAME} PRIVATE bgfx bx bimg)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/build/extern/SDL/Debug/SDL3.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>)