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

#Libraries
set(ALLEGRO_LIBS allegro allegro_main)							#Main Allegro libraries.
set(ALLEGRO_LIBS ${ALLEGRO_LIBS} allegro_image)					#Graphics plugins.
set(ALLEGRO_LIBS ${ALLEGRO_LIBS} allegro_audio allegro_acodec)	#Audio plugins.
set(ALLEGRO_LIBS ${ALLEGRO_LIBS} allegro_physfs)				#Physfs plugin.
set(ALLEGRO_LIBS ${ALLEGRO_LIBS} allegro_font allegro_ttf)		#Font plugins.
set(ALLEGRO_LIBS ${ALLEGRO_LIBS} allegro_dialog)				#Dialog box plugin.

#Binary
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
add_executable(${CMAKE_PROJECT_NAME} ${ENGINE_SOURCES} ${GAME_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${ALLEGRO_LIBS} physfs)
