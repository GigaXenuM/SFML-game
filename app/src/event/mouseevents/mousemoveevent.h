#pragma once

#include "event/event.h"

class MouseMoveEvent : public Event
{
public:
    explicit MouseMoveEvent(double x, double y);

    EventType type() const override
    {
        return EventType::MOUSE_MOVE;
    }

    double x() const;
    double y() const;

private:
    double _x;
    double _y;
};
