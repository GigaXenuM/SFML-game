#pragma once

#include "event/event.h"

#include "event/mouseevents/mouse.h"

class MousePressEvent : public Event
{
public:
    MousePressEvent(Mouse::Button button);

    EventType type() const override
    {
        return EventType::MOUSE_PRESS;
    }

    Mouse::Button button() const;

private:
    Mouse::Button _button;
};
