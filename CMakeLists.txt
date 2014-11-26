project(floodit-allegro)
cmake_minimum_required(VERSION 2.8)
add_definitions(-DMT_NO_INLINE)
add_definitions(-DMT_NO_LONGLONG)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

aux_source_directory(. SRC_LIST)

aux_source_directory(allegro-shell SRC_LIST_APPEND)
list(APPEND SRC_LIST ${SRC_LIST_APPEND})

aux_source_directory(core SRC_LIST_APPEND)
list(APPEND SRC_LIST ${SRC_LIST_APPEND})

aux_source_directory(mtwist SRC_LIST_APPEND)
list(APPEND SRC_LIST ${SRC_LIST_APPEND})

aux_source_directory(shell SRC_LIST_APPEND)
list(APPEND SRC_LIST ${SRC_LIST_APPEND})

aux_source_directory(jsmn SRC_LIST_APPEND)
list(APPEND SRC_LIST ${SRC_LIST_APPEND})

find_package(Allegro5 REQUIRED)

#include_directories(/usr/include/allegro5)
#link_directories(/usr/lib)

set(floodit-allegro_LINK_LIBS )

if(VS2013)
	add_definitions(-DALLEGRO_HAVE_STDBOOL_H)
endif(VS2013)

include_directories(include ${ALLEGRO_INCLUDE_DIR})
#list(APPEND floodit-allegro_LINK_LIBS ${allegro_LIBRARIES})

file(GLOB_RECURSE HEADER_LIST "*.h")
add_executable(floodit-allegro ${SRC_LIST} ${HEADER_LIST})

#target_link_libraries(floodit-allegro liballegro.so)
#target_link_libraries(floodit-allegro liballegro_dialog.so)
#target_link_libraries(floodit-allegro liballegro_font.so)
target_link_libraries(floodit-allegro ${ALLEGRO_LIBRARIES})

if(ALLEGRO_W)
	string(REGEX REPLACE "a+$" "dll" ALLEGRO_W "${ALLEGRO_W}")
	string(REGEX REPLACE "/lib/" "/bin/" ALLEGRO_W "${ALLEGRO_W}")
	string(REGEX REPLACE "/lib" "/" ALLEGRO_W "${ALLEGRO_W}")
	file(COPY ${ALLEGRO_W} DESTINATION .)
endif(ALLEGRO_W)

file(COPY resources DESTINATION .)
file(COPY config.dad DESTINATION .)
