#This CMake file is only known to work on Linux.
#Having Allegro 5 and physfs libraries installed is also required.
#
#If you want to build this under Windows, you're going to have to use
#some other method for building for now.
cmake_minimum_required (VERSION 2.6)
project (taiga)
set(CMAKE_CXX_FLAGS "-std=c++0x -O3 -s")

#Includes
include_directories("${PROJECT_SOURCE_DIR}/engine")
include_directories("${PROJECT_SOURCE_DIR}/game")

#Sources
aux_source_directory("${PROJECT_SOURCE_DIR}/engine" ENGINE_SOURCES)
aux_source_directory("${PROJECT_SOURCE_DIR}/game" GAME_SOURCES)

#Binary
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
add_executable(${CMAKE_PROJECT_NAME} ${ENGINE_SOURCES} ${GAME_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} allegro allegro_main allegro_image allegro_audio allegro_acodec allegro_physfs allegro_dialog allegro_font allegro_ttf physfs)
