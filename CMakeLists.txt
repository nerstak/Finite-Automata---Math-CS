cmake_minimum_required(VERSION 3.12)
project(Finite_Automata___Math_CS)

set(CMAKE_CXX_STANDARD 14)

FILE(GLOB_RECURSE SRC "src/*.c")
FILE(GLOB_RECURSE HDR "src/*.h")

set(MAIN main.cpp)

add_executable(Finite_Automata___Math_CS ${MAIN} ${SRC} ${HDR})