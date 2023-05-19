cmake_minimum_required(VERSION 3.15)

project(tp)

set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)
add_subdirectory(libs/libSDL2pp-0.18.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${SDL2PP_INCLUDE_DIRS})

add_executable(Client ${PROJECT_SOURCE_DIR}/Client/src/main.cpp Client/src/client.cpp)

target_link_libraries(Client PUBLIC SDL2pp)

file(COPY Resources DESTINATION ${CMAKE_BINARY_DIR})