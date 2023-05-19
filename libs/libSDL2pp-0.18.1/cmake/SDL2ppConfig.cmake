find_package(SDL2 REQUIRED)

if(ON)
	find_package(SDL2_image REQUIRED)
endif()

if(ON)
	find_package(SDL2_ttf REQUIRED)
endif()

if(ON)
	find_package(SDL2_mixer REQUIRED)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/SDL2ppTargets.cmake")
