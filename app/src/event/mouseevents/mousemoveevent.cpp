#include "mousemoveevent.h"

MouseMoveEvent::MouseMoveEvent(PointF pos, PointF lastPos) : _pos{ pos }, _lastPos{ lastPos }
{
}

PointF MouseMoveEvent::pos() const
{
    return _pos;
}

PointF MouseMoveEvent::lastPos() const
{
    return _lastPos;
}
