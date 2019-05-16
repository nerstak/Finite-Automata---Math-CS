cmake_minimum_required(VERSION 3.6) # Version for CMake
project(Finite_Automata___Math_CS) # Project name

#List of files
# List of cpp files
set(SRC
        main.cpp
        src/complementary.cpp
        src/completion.cpp
        src/determinization.cpp
        src/FA.cpp
        src/files.cpp
        src/reading.cpp
        src/standardization.cpp
        src/State.cpp
        src/reading.cpp
        src/minimization.cpp
        src/Transition.cpp)


# List of h files
set(HDR
        src/determinization.h
        src/completion.h
        src/FA.h
        src/files.h
        src/State.h
        src/reading.h
        src/minimization.h
        src/Transition.h src/mainLoop.cpp src/mainLoop.h)

set(CMAKE_CXX_STANDARD 17) # Version of C++
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../) # Output in root folder

add_executable(Finite_Automata___Math_CS ${SRC} ${HDR})