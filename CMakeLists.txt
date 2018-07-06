cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME Molecule_Visualizer)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")

include_directories(include)
link_directories(libs)

add_executable(${PROJECT_NAME}
        src/Atom.cpp
        src/Atom.h
        src/Connection.cpp
        src/Connection.h
        src/Driver.cpp
        src/Molecule.cpp
        src/Molecule.h
        src/PeriodicTable.cpp
        src/PeriodicTable.h
        src/Drawable.cpp
        src/Drawable.h src/Viewport.h src/Camera.h src/Camera.cpp src/Viewport.cpp)

target_link_libraries(${PROJECT_NAME} GLEW glfw3 -m64)
