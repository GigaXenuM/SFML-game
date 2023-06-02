#include "mousemoveevent.h"

MouseMoveEvent::MouseMoveEvent(double x, double y) : _x{ x }, _y{ y }
{
}

double MouseMoveEvent::x() const
{
    return _x;
}

double MouseMoveEvent::y() const
{
    return _y;
}
