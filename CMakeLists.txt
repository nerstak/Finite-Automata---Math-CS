cmake_minimum_required(VERSION 3.12) # Version for CMake
project(Finite_Automata___Math_CS) # Project name

#List of files
# List of cpp files
set(SRC
        main.cpp
        src/FA.cpp
        src/files.cpp
        src/determinization.cpp
        src/Transition.cpp
        src/State.cpp)

# List of h files
set(HDR
        src/FA.h
        src/files.h
        src/determinization.h
        src/Transition.h
        src/State.h)

set(MAIN main.cpp src/State.cpp src/State.h)

set(CMAKE_CXX_STANDARD 17) # Version of C++
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../) # Output in root folder

add_executable(Finite_Automata___Math_CS ${MAIN} ${SRC} ${HDR})