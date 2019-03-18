cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME Molecule_Visualizer)
project(${PROJECT_NAME})

if(WIN32 OR MSVC OR MSYS OR MINGW)
    set(CMAKE_C_COMPILER C:/mingw-m64/mingw64/bin/gcc.exe)
    set(CMAKE_CXX_COMPILER C:/mingw-m64/mingw64/bin/g++.exe)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if(APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
endif()

include_directories(include)
link_directories(libs)
if(WIN32 OR MSVC OR MSYS OR MINGW)
    link_directories(bin)
endif()

add_executable(${PROJECT_NAME}
        src/Atom.cpp
        src/Atom.h
        src/Connection.cpp
        src/Connection.h
        src/Driver.cpp
        src/Molecule.cpp
        src/Molecule.h
        src/Drawable.h
        src/Drawable.cpp
        src/Viewport.h
        src/Viewport.cpp
        src/Camera.h
        src/Camera.cpp)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} GLEW glfw3 -m64)
endif()

if(WIN32 OR MSVC OR MSYS OR MINGW)
    target_link_libraries(${PROJECT_NAME} glew32 glfw3 opengl32 -m64)
endif()
