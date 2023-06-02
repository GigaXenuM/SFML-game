#include "keyreleaseevent.h"

KeyReleaseEvent::KeyReleaseEvent(Keyboard::Key key) : _key{ key }
{
}

Keyboard::Key KeyReleaseEvent::key() const
{
    return _key;
}
