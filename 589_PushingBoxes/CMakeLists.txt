cmake_minimum_required(VERSION 3.8)
set(PROBLEM_NR "589")
project(${PROBLEM_NR} CXX)

add_compile_options(-lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE)

add_custom_command(
  # TARGET ${PROBLEM_NR} POST_BUILD
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/input.txt
  COMMAND ${CMAKE_COMMAND} 
        -E copy_if_different
                ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
                ${CMAKE_CURRENT_BINARY_DIR}/input.txt
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
  VERBATIM)

add_executable(${PROBLEM_NR} main.cpp ${CMAKE_CURRENT_BINARY_DIR}/input.txt)