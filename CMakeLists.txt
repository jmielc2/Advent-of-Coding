cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project("advent-of-coding")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
add_library(ctools STATIC include/ctools.c)
# message(${ARCHIVE_OUTPUT_DIRECTORY}/lib)

add_subdirectory(12-1-2022)