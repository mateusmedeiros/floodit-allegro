project(floodit-allegro)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -ansi -pedantic")
add_definitions(-DMT_NO_INLINE)
add_definitions(-DMT_NO_LONGLONG)


aux_source_directory(. SRC_LIST)


aux_source_directory(allegro-shell SRC_LIST_APPEND)
list(APPEND SRC_LIST ${SRC_LIST_APPEND})

aux_source_directory(core SRC_LIST_APPEND)
list(APPEND SRC_LIST ${SRC_LIST_APPEND})

aux_source_directory(mtwist SRC_LIST_APPEND)
list(APPEND SRC_LIST ${SRC_LIST_APPEND})

aux_source_directory(shell SRC_LIST_APPEND)
list(APPEND SRC_LIST ${SRC_LIST_APPEND})

include_directories(/usr/include/allegro5)
link_directories(/usr/lib)

file(GLOB_RECURSE HEADER_LIST "*.h")
add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADER_LIST})

target_link_libraries(${PROJECT_NAME} liballegro.so)
target_link_libraries(${PROJECT_NAME} liballegro_dialog.so)
target_link_libraries(${PROJECT_NAME} liballegro_font.so)
target_link_libraries(${PROJECT_NAME} liballegro_ttf.so)


file(COPY resources DESTINATION .)
