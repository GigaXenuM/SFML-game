#include "menuview.h"

#include "geometry/utils.h"

MenuView::MenuView(RectF rect, EventHandler *parent) : sf::View{ Geometry::toSfmlRect(rect) }
{
    if (parent != nullptr)
        parent->addEventHandler(this);
}
