#include "keypressevent.h"

KeyPressEvent::KeyPressEvent(Keyboard::Key key) : _key{ key }
{
}

Keyboard::Key KeyPressEvent::key() const
{
    return _key;
}
