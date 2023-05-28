include(FetchContent)

FETCHCONTENT_DECLARE(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1)

FETCHCONTENT_MAKEAVAILABLE(googletest)
add_library(GTest::Gtest INTERFACE IMPORTED)
target_link_libraries(GTest::Gtest INTERFACE gtest_main)

#-----------------Include Directories-----------------#
include_directories(${PROJECT_SOURCE_DIR}/Common/include)
include_directories(${PROJECT_SOURCE_DIR}/Server/include)
# include_directories(${PROJECT_SOURCE_DIR}/Client/include)

#-----------------Test Executables-----------------#
# Se debe añadir TODOS los archivos fuente (.cpp) de lo que utiliza el programa.
# Si se olvidan de alguno les tira 'undefined reference to <method>'.
add_executable(resolver_test resolver_test.cpp
        ${PROJECT_SOURCE_DIR}/Common/src/resolver.cpp)
add_executable(actiondto_test actiondto_test.cpp
        ../Common/src/Action/action_dto.cpp)
add_executable(gamemanager_test gamemanager_test.cpp
        ../Server/src/game_manager.cpp
        ../Server/src/game.cpp
        ../Server/src/Command/command.cpp)

find_package(GTest REQUIRED)

#----------------Linking Executables----------------#
# Siempre lo mismo, así funciona gtest
target_link_libraries(resolver_test
        PRIVATE
        GTest::GTest)
target_link_libraries(actiondto_test PRIVATE GTest::GTest)
target_link_libraries(gamemanager_test PRIVATE GTest::GTest)


#-----------------Adding Tests-----------------#
# Siempre lo mismo tambien.
add_test(resolver_gtests resolver_test WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(actiondto_gtests actiondto_test WORKING_DIRECTORY
        ${PROJECT_SOURCE_DIR})
add_test(gamemanager_gtest gamemanager_test WORKING_DIRECTORY
        ${PROJECT_SOURCE_DIR})

#TODO
#Los tests en el .cpp deben incluir TODOS los .h de las clases que utilizan
#en su implementación. Esto puede resultar incómodo y requiere un cambio en
#el Cmake para que no haga falta incluirlos así, sino que incluya
#automáticamente lo que necesita.