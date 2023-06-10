include(FetchContent)

FETCHCONTENT_DECLARE(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1)

FETCHCONTENT_MAKEAVAILABLE(googletest)
add_library(GTest::Gtest INTERFACE IMPORTED)
target_link_libraries(GTest::Gtest INTERFACE gtest_main)


add_definitions(-DSERVER_CONFIG_PATH="${PROJECT_SOURCE_DIR}/Server/config")

#-----------------Include Directories-----------------#
include_directories(${PROJECT_SOURCE_DIR}/Common/include)
include_directories(${PROJECT_SOURCE_DIR}/Server/include)
# include_directories(${PROJECT_SOURCE_DIR}/Client/include)

file(GLOB_RECURSE GAMELOGIC_SOURCES "${PROJECT_SOURCE_DIR}/Server/src/GameLogic/*.cpp")
file(GLOB_RECURSE COMMAND_SOURCES "${PROJECT_SOURCE_DIR}/Server/src/Command/*.cpp")
file(GLOB_RECURSE INFORMATION_SOURCES "${PROJECT_SOURCE_DIR}/Common/src/Information/*.cpp")

function(run_test NAME SOURCES)
    add_executable(${NAME}_test ${NAME}_test.cpp
            ${SOURCES})
    target_link_libraries(${NAME}_test PRIVATE GTest::GTest)
    add_test(${NAME}_gtests ${NAME}_test WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endfunction()
#-----------------Test Executables-----------------#
# Se debe añadir TODOS los archivos fuente (.cpp) de lo que utiliza el programa.
# Si se olvidan de alguno les tira 'undefined reference to <method>'.
add_executable(resolver_test resolver_test.cpp
        ${PROJECT_SOURCE_DIR}/Common/src/resolver.cpp)
add_executable(information_test information_test.cpp
        ${INFORMATION_SOURCES})
add_executable(gamemanager_test gamemanager_test.cpp
        ../Server/src/game_manager.cpp
        ../Server/src/game.cpp
        ../Server/src/Command/command_ingame_startshoot.cpp
        ../Server/src/Command/command_ingame.cpp
        ${INFORMATION_SOURCES}
        ${GAMELOGIC_SOURCES})

add_executable(command_test command_test.cpp
        ../Server/src/game_manager.cpp
        ../Server/src/game.cpp
        ${COMMAND_SOURCES}
        ${GAMELOGIC_SOURCES}
        ${INFORMATION_SOURCES})
add_executable(soldier_test soldier_test.cpp
        ${INFORMATION_SOURCES}
        ${GAMELOGIC_SOURCES})
add_executable(weapon_test weapon_test.cpp
        ${INFORMATION_SOURCES}
        ${GAMELOGIC_SOURCES})
add_executable(match_test match_test.cpp
        ${INFORMATION_SOURCES}
        ${GAMELOGIC_SOURCES})

find_package(GTest REQUIRED)

#----------------Linking Executables----------------#
# Siempre lo mismo, así funciona gtest
target_link_libraries(resolver_test PRIVATE GTest::GTest yaml-cpp)
target_link_libraries(information_test PRIVATE GTest::GTest yaml-cpp)
target_link_libraries(gamemanager_test PRIVATE GTest::GTest yaml-cpp)
target_link_libraries(command_test PRIVATE GTest::GTest yaml-cpp)
target_link_libraries(soldier_test PRIVATE GTest::GTest yaml-cpp)
target_link_libraries(weapon_test PRIVATE GTest::GTest yaml-cpp)
target_link_libraries(match_test PRIVATE GTest::GTest yaml-cpp)

#-----------------Adding Tests-----------------#
# Siempre lo mismo tambien.
add_test(resolver_gtests resolver_test WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(information_gtests information_test WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(gamemanager_gtest gamemanager_test WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(command_gtest command_test WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(soldier_gtest soldier_test WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(weapon_gtest weapon_test WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(match_gtest match_test WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})


#TODO
#Los tests en el .cpp deben incluir TODOS los .h de las clases que utilizan
#en su implementación. Esto puede resultar incómodo y requiere un cambio en
#el Cmake para que no haga falta incluirlos así, sino que incluya
#automáticamente lo que necesita.
