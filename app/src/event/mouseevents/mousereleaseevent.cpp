#include "mousereleaseevent.h"

MouseReleaseEvent::MouseReleaseEvent(Mouse::Button button) : _button{ button }
{
}

Mouse::Button MouseReleaseEvent::button() const
{
    return _button;
}
