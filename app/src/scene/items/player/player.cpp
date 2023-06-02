#include "player.h"

#include "event/keyevents/keyboard.h"
#include "event/keyevents/keypressevent.h"
#include "event/keyevents/keyreleaseevent.h"

namespace Scene
{
Player::Player(EventHandler *parent) : Item{ parent }, _drawableItem{ 100.f }
{
    _drawableItem.setFillColor(sf::Color::Green);
}

const sf::Drawable &Player::drawableItem() const
{
    return _drawableItem;
}

void Player::keyPressEvent(KeyPressEvent *event)
{
    float speed{ 20 };
    if (event->key() == Keyboard::Key::A)
        _drawableItem.move({ -speed, .0f });
    if (event->key() == Keyboard::Key::D)
        _drawableItem.move({ speed, .0f });
    if (event->key() == Keyboard::Key::W)
        _drawableItem.move({ .0f, -speed });
    if (event->key() == Keyboard::Key::S)
        _drawableItem.move({ .0f, speed });
}

void Player::keyReleaseEvent(KeyReleaseEvent *event)
{
}
} // namespace Scene
