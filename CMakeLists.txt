cmake_minimum_required(VERSION 3.15)
# TODO: setear flags de compilacion
project(tp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)

add_subdirectory(libs/libSDL2pp-0.18.1)
add_subdirectory(tests)

add_definitions(-DRESOURCES_PATH="${PROJECT_SOURCE_DIR}/Resources")
add_definitions(-DCLIENT_CONFIG_PATH="${PROJECT_SOURCE_DIR}/Client/config")

include_directories(${SDL2PP_INCLUDE_DIRS})

file(GLOB CLIENT_SOURCES "${PROJECT_SOURCE_DIR}/Client/src/*.cpp")
file(GLOB COMMON_SOURCES "${PROJECT_SOURCE_DIR}/Common/src/*.cpp")

add_executable(Client ${CLIENT_SOURCES} ${COMMON_SOURCES})

target_link_libraries(Client PUBLIC SDL2pp yaml-cpp)

file(COPY Resources DESTINATION ${CMAKE_BINARY_DIR})

enable_testing()