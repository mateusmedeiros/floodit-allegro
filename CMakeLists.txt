project(floodit-allegro)
cmake_minimum_required(VERSION 2.8)

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

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} liballegro.so)
