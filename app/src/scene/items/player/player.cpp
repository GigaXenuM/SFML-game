#include "player.h"

#include "event/keyevents/keyboard.h"
#include "event/keyevents/keypressevent.h"
#include "event/keyevents/keyreleaseevent.h"

namespace Scene
{
Player::Player(EventHandler *parent) : Item{ parent }, _drawableItem{ 50.f }, _keyStates{ false }
{
    _drawableItem.setFillColor(sf::Color::Green);
}

const sf::Drawable &Player::drawableItem() const
{
    return _drawableItem;
}

void Player::update()
{
    move();
}

void Player::keyPressEvent(KeyPressEvent *event)
{
    _keyStates[static_cast<size_t>(event->key())] = true;
}

void Player::keyReleaseEvent(KeyReleaseEvent *event)
{
    _keyStates[static_cast<size_t>(event->key())] = false;
}

void Player::move()
{
    using Keyboard::Key;

    float speed{ 0.05f };
    if (_keyStates[static_cast<size_t>(Key::A)])
        _drawableItem.move({ -speed, .0f });
    if (_keyStates[static_cast<size_t>(Key::D)])
        _drawableItem.move({ speed, .0f });
    if (_keyStates[static_cast<size_t>(Key::W)])
        _drawableItem.move({ .0f, -speed });
    if (_keyStates[static_cast<size_t>(Key::S)])
        _drawableItem.move({ .0f, speed });
}
} // namespace Scene
