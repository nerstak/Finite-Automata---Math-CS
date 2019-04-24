cmake_minimum_required(VERSION 3.12) # Version for CMake
project(Finite_Automata___Math_CS) # Project name

#List of files
# List of cpp files
set(SRC
        main.cpp
        src/structure.cpp
        src/files.cpp
        )

# List of h files
set(HDR
        src/structure.h
        src/files.h
        )
set(MAIN main.cpp)

set(CMAKE_CXX_STANDARD 14) # Version of C++
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../) # Output in root folder

add_executable(Finite_Automata___Math_CS ${MAIN} ${SRC} ${HDR})