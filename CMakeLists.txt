cmake_minimum_required(VERSION 3.10)
project(Meta-Prog-Cpp CXX)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "-pg") - use only with GCC 's own profiler

# Source
set (_HEADER_
  ./command.h
  ./Test.h
)

set (_SOURCES_
  ./main.cpp
)

add_executable(${PROJECT_NAME} ${_SOURCES_} ${_HEADER_})
