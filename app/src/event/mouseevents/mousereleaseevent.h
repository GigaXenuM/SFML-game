#pragma once

#include "event/event.h"

#include "event/mouseevents/mouse.h"

class MouseReleaseEvent : public Event
{
public:
    MouseReleaseEvent(Mouse::Button button);

    EventType type() const override
    {
        return EventType::MOUSE_RELEASE;
    }

    Mouse::Button button() const;

private:
    Mouse::Button _button;
};
