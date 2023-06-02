cmake_minimum_required(VERSION 3.20)

set(HEADER_FILES
    src/mainwindow.h

    src/scene/scene.h
    src/scene/items/player/player.h
    src/scene/items/item.h

    src/event/event.h
    src/event/eventhandler.h
    src/event/keyevents/keyboard.h
    src/event/keyevents/keypressevent.h
    src/event/keyevents/keyreleaseevent.h
)

set(SOURCE_FILES
    src/main.cpp

    src/mainwindow.cpp

    src/scene/scene.cpp
    src/scene/items/player/player.cpp

    src/event/eventhandler.cpp
    src/event/keyevents/keypressevent.cpp
    src/event/keyevents/keyreleaseevent.cpp
)

include_directories(
    "${CMAKE_SOURCE_DIR}/app/src"
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} )

target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_link_libraries(${PROJECT_NAME} sfml-audio)
