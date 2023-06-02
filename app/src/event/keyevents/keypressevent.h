#pragma once

#include "event/event.h"

#include "event/keyevents/keyboard.h"

class KeyPressEvent : public Event
{
public:
    explicit KeyPressEvent(Keyboard::Key key);
    virtual ~KeyPressEvent() = default;

    EventType type() const override
    {
        return EventType::KEY_PRESS;
    }

    Keyboard::Key key() const;

private:
    Keyboard::Key _key;
};
