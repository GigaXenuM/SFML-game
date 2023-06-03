#include "player.h"

#include "event/keyevents/keyboard.h"
#include "event/keyevents/keypressevent.h"
#include "event/keyevents/keyreleaseevent.h"

#include "geometry/utils.h"

namespace Scene
{
Player::Player(EventHandler *parent)
    : CollisionItem{ parent }, _drawableItem{ 50.f }, _keyStates{ false }
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

void Player::setPos(PointF position)
{
    _drawableItem.setPosition({ position.x, position.y });
}

void Player::handleCollision(RectF collisionRect)
{
    if (collisionRect.height() > collisionRect.width())
    {
        // From left
        if (center().x > collisionRect.pos.x)
            _drawableItem.move({ collisionRect.width(), .0f });
        // From right
        else
            _drawableItem.move({ -collisionRect.width(), .0f });
    }
    else
    {
        // From top
        if (center().y > collisionRect.pos.y)
            _drawableItem.move({ .0f, collisionRect.height() });
        // From bottom
        else
            _drawableItem.move({ .0f, -collisionRect.height() });
    }
}

PointF Player::center() const
{
    auto sfmlPos{ _drawableItem.getPosition() };
    float radius{ _drawableItem.getRadius() };
    return { sfmlPos.x + radius, sfmlPos.y + radius };
}

std::optional<RectF> Player::intersects(const Item &item) const
{
    std::optional<sf::FloatRect> sfmlRect{ _drawableItem.getGlobalBounds().findIntersection(
        Geometry::toSfmlRectF(item.globalRect())) };

    if (sfmlRect.has_value())
        return Geometry::toRectF(sfmlRect.value());

    return std::nullopt;
}

RectF Player::globalRect() const
{
    return Geometry::toRectF(_drawableItem.getGlobalBounds());
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
