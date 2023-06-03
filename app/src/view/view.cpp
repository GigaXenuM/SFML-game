#include "view.h"

#include "event/mouseevents/mousemoveevent.h"
#include "event/mouseevents/mousepressevent.h"
#include "event/mouseevents/mousereleaseevent.h"

View::View(RectF rect, EventHandler *parent)
    : sf::View{ { rect.pos.x, rect.pos.y }, { rect.size.width, rect.size.height } }
{
    if (parent != nullptr)
        parent->addEventHandler(this);
}

void View::mousePressEvent(MousePressEvent *event)
{
    if (event->button() == Mouse::Button::Middle)
        _canDrag = true;
}

void View::mouseReleaseEvent(MouseReleaseEvent *event)
{
    if (event->button() == Mouse::Button::Middle)
        _canDrag = false;
}

void View::mouseMoveEvent(MouseMoveEvent *event)
{
    if (!_canDrag)
        return;

    PointF delta{ event->lastPos() - event->pos() };
    move({ delta.x, delta.y });
}
