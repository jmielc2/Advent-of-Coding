cmake_minimum_required(VERSION 3.22)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/12-1-2022)

# CPP Version
project("main-cpp")
add_executable(${PROJECT_NAME} main.cpp)

# C Version
project("main-c")
add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} ctools)