#pragma once

#include "event/event.h"

#include "event/keyevents/keyboard.h"

class KeyReleaseEvent : public Event
{
public:
    explicit KeyReleaseEvent(Keyboard::Key key);
    virtual ~KeyReleaseEvent() = default;

    EventType type() const override
    {
        return EventType::KEY_RELEASE;
    }

    Keyboard::Key key() const;

private:
    Keyboard::Key _key;
};
