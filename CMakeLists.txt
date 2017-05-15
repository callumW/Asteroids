cmake_minimum_required (VERSION 2.8)
project (Asteroids C)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")
set(SDL_MIXER_INCLUDE_DIR "SDL_Mixer includes" CACHE PATH "description")
set(SDL_MIXER_LIB "SDL_Mixer lib" CACHE FILEPATH "description")


file (GLOB SRC_FILES src/*.c)

#copy media folder into build directory if we are building outside of source
if (NOT CMAKE_CURRENT_BINARY_DIR EQUAL CMAKE_CURRENT_SOURCE_DIR)
    file (GLOB MEDIA_FILES "media/*")
    file (COPY ${MEDIA_FILES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/media")
endif (NOT CMAKE_CURRENT_BINARY_DIR EQUAL CMAKE_CURRENT_SOURCE_DIR)
add_executable (Asteroids ${SRC_FILES})

#find_library (SDL_LIBRARY NAMES SDL2 SDL PATHS
#    /Library/Framworks
#    C:/SDL2)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
message("SDL2DIR: " $ENV{SDL2DIR})

find_package (SDL2 REQUIRED)
find_package (OpenGL REQUIRED)

message ("OPENGL_LIBRARY: ${OPENGL_LIBRARY}")
message ("SDL2 Include path: ${SDL2_INCLUDE_DIR}")
message ("SDL2 Links: ${SDL2_LIBRARY}")


include_directories (${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${SDL_MIXER_INCLUDE_DIR})
target_link_libraries (Asteroids ${SDL2_LIBRARY} ${OPENGL_LIBRARY} ${SDL_MIXER_LIB})
