cmake_minimum_required(VERSION 3.10)
project(Meta-Prog-Cpp CXX)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "-pg") - use only with GCC 's own profiler

# Source
set (_HEADER_
  ./command.h
  ./static_keys_map.h
  ./sfine_example.h
  ./stdfunction_impl.h
  ./stdUnique_Impl.h
  ./variadic_tem_std_unique.h
  ./fold_expr_std_unique.h
  ./constexpr_std_unique_stl.h
)

set (_SOURCES_
  ./main.cpp
)

add_executable(${PROJECT_NAME} ${_SOURCES_} ${_HEADER_})
