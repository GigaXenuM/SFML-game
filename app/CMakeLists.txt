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
    src/scene/itemcontext.h
    src/scene/visitors/ivisitor.h
    src/scene/visitors/defaultvisitor.h
    src/scene/visitors/sortitemsvisitor.h
    src/scene/items/player/player.h
    src/scene/items/drawable.h
    src/scene/items/item.h
    src/scene/items/collisionitem.h
    src/scene/items/rectangles/collisionrect.h
    src/scene/items/rectangles/rect.h
    src/scene/items/collisionhandler.h
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

    src/scene/tip/itip.h
)

set(SOURCE_FILES
    src/main.cpp

    src/mainwindow.cpp

    src/view/sceneview.cpp
    src/view/menuview.cpp

    src/layout/layout.cpp
    src/layout/verticallayout.cpp

    src/scene/scene.cpp
    src/scene/visitors/defaultvisitor.cpp
    src/scene/visitors/sortitemsvisitor.cpp
    src/scene/items/item.cpp
    src/scene/items/collisionitem.cpp
    src/scene/items/player/player.cpp
    src/scene/items/rectangles/collisionrect.cpp
    src/scene/items/rectangles/rect.cpp
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
    "${CMAKE_SOURCE_DIR}/app/src/scene"
    "${CMAKE_SOURCE_DIR}/app/src/geometry"
    "${CMAKE_SOURCE_DIR}/app/src/menu"
    "${CMAKE_SOURCE_DIR}/app/src/view"
    "${CMAKE_SOURCE_DIR}/app/src/layout"
    "${CMAKE_SOURCE_DIR}/app/src/event"
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} )

target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_link_libraries(${PROJECT_NAME} sfml-audio)
