cmake_minimum_required(VERSION 3.10)
project(MultiThreading-Cpp CXX)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "-pg") - use only with GCC 's own profiler

# Source
set (_HEADER_
  ./command.h
  ./hft_prob_1.h
  ./hft_prob_2.h
  ./hft_prob_3.h
  ./hft_prob_4.h
)

set (_SOURCES_
  ./main.cpp
)

add_executable(${PROJECT_NAME} ${_SOURCES_} ${_HEADER_})
