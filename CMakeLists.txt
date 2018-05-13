cmake_minimum_required(VERSION 3.10)
project(Molecule_Visualizer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
#set(CMAKE_CXX_FLAGS -m32)
#set(CMAKE_C_FLAGS -m32)

include_directories(include)
link_directories(libs)

add_executable(Molecule_Visualizer
        src/Atom.cpp
        src/Atom.h
        src/Connection.cpp
        src/Connection.h
        src/Driver.cpp
        src/Molecule.cpp
        src/Molecule.h
        src/PeriodicTable.cpp
        src/PeriodicTable.h)

#set_target_properties(Molecule_Visualizer PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

find_library(GLEW_LIBRARY GLEW)
find_library(GLFW3_LIBRARY glfw3)


link_libraries(Molecule_Visualizer ${GLEW_LIBRARY} ${GLFW3_LIBRARY} -m64)
