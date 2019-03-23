cmake_minimum_required(VERSION 3.13)
project(CSI3344Program1)

set(CMAKE_CXX_FLAGS "${SMAKE_CXX_FLAGS}  -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories(${PROJECT_SOURCE_DIR}/i686-w64-mingw32/include)
link_directories(${PROJECT_SOURCE_DIR}/i686-w64-mingw32/lib)

set(SOURCE_FILES main.cpp point.h color_rgb.cpp curve.cpp line.cpp point.cpp
       color_rgb.h curve.h line.h SDL_Plotter.h convexHull.cpp closest_pair.cpp
        font.cpp font.h)

add_executable(CSI3344Program1 ${SOURCE_FILES})

target_link_libraries(CSI3344Program1 mingw32 SDL2main SDL2 SDL2_mixer)