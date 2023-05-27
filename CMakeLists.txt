cmake_minimum_required(VERSION 3.15)

project(tp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0 -Werror -pedantic -pedantic-errors")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -fno-inline")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)

add_subdirectory(libs/libSDL2pp-0.18.1)
add_subdirectory(tests)

add_definitions(-DRESOURCES_PATH="${PROJECT_SOURCE_DIR}/Resources")
add_definitions(-DCLIENT_CONFIG_PATH="${PROJECT_SOURCE_DIR}/Client/config")

include_directories(${SDL2PP_INCLUDE_DIRS})

file(GLOB_RECURSE CLIENT_SOURCES "${PROJECT_SOURCE_DIR}/Client/src/*.cpp")
file(GLOB_RECURSE COMMON_SOURCES "${PROJECT_SOURCE_DIR}/Common/src/*.cpp")
file(GLOB_RECURSE SERVER_SOURCES "${PROJECT_SOURCE_DIR}/Server/src/*.cpp")

add_executable(Client ${CLIENT_SOURCES} ${COMMON_SOURCES})
add_executable(Server ${SERVER_SOURCES} ${COMMON_SOURCES})

target_link_libraries(Client PUBLIC SDL2pp yaml-cpp)

file(COPY Resources DESTINATION ${CMAKE_BINARY_DIR})

enable_testing()