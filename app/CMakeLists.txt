cmake_minimum_required(VERSION 3.20)

set(HEADER_FILES
    src/mainwindow.h

    src/ibutton.h

    src/view/iview.h
    src/view/sceneview.h
    src/view/menuview.h

    src/layout/layout.h
    src/layout/verticallayout.h

    src/irenderer.h
    src/idrawable.h

    src/scene/scene.h
    src/scene/items/player/player.h
    src/scene/items/item.h
    src/scene/items/testitem.h
    src/scene/items/collisionitem.h
    src/scene/items/button/textbutton.h
    src/scene/animation/animation.h
    src/scene/textures/textures.h

    src/event/event.h
    src/event/eventhandler.h
    src/event/keyevents/keyboard.h
    src/event/keyevents/keypressevent.h
    src/event/keyevents/keyreleaseevent.h
    src/event/mouseevents/mousepressevent.h
    src/event/mouseevents/mousemoveevent.h
    src/event/mouseevents/mousereleaseevent.h
    src/event/mouseevents/mouse.h

    src/geometry/point.h
    src/geometry/rect.h
    src/geometry/size.h
    src/geometry/utils.h
    src/geometry/alignment.h

    src/menu/menu.h
)

set(SOURCE_FILES
    src/main.cpp

    src/mainwindow.cpp

    src/view/sceneview.cpp
    src/view/menuview.cpp

    src/layout/layout.cpp
    src/layout/verticallayout.cpp

    src/scene/scene.cpp
    src/scene/items/item.cpp
    src/scene/items/player/player.cpp
    src/scene/items/testitem.cpp
    src/scene/items/button/textbutton.cpp
    src/scene/animation/animation.cpp
    src/scene/textures/textures.cpp

    src/event/eventhandler.cpp
    src/event/keyevents/keypressevent.cpp
    src/event/keyevents/keyreleaseevent.cpp
    src/event/mouseevents/mousepressevent.cpp
    src/event/mouseevents/mousemoveevent.cpp
    src/event/mouseevents/mousereleaseevent.cpp

    src/geometry/utils.cpp

    src/menu/menu.cpp
)

include_directories(
    "${CMAKE_SOURCE_DIR}/app/src"
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} )

target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_link_libraries(${PROJECT_NAME} sfml-audio)
