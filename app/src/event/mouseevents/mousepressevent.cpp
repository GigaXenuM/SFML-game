#include "mousepressevent.h"

MousePressEvent::MousePressEvent(Mouse::Button button) : _button{ button }
{
}

Mouse::Button MousePressEvent::button() const
{
    return _button;
}
