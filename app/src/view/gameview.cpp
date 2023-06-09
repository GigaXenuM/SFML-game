#include "gameview.h"

#include "event/mouseevents/mousemoveevent.h"
#include "event/mouseevents/mousepressevent.h"
#include "event/mouseevents/mousereleaseevent.h"

#include "geometry/utils.h"

GameView::GameView(RectF rect, EventHandler *parent)
    : sf::View{ { rect.pos.x, rect.pos.y }, { rect.size.width, rect.size.height } }
{
    if (parent != nullptr)
        parent->addEventHandler(this);
}

void GameView::mousePressEvent(MousePressEvent *event)
{
    if (event->button() == Mouse::Button::Middle)
        _canDrag = true;
}

void GameView::mouseReleaseEvent(MouseReleaseEvent *event)
{
    if (event->button() == Mouse::Button::Middle)
        _canDrag = false;
}

void GameView::mouseMoveEvent(MouseMoveEvent *event)
{
    if (!_canDrag)
        return;

    PointF delta{ event->lastPosition() - event->position() };
    move(Geometry::toSfmlPoint(delta));
}
