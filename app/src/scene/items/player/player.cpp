#include "player.h"

#include "event/keyevents/keyboard.h"
#include "event/keyevents/keypressevent.h"
#include "event/keyevents/keyreleaseevent.h"

#include "geometry/utils.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Time.hpp"

#include <iostream>

namespace Scene
{
Player::Player(std::shared_ptr<sf::Texture> texture, EventHandler *parent)
    : CollisionHandler{ parent },
      _texture{ std::move(texture) },
      _drawableItem{ *_texture },
      _animation{ _texture, 4, 8, 0.25f },
      _keyStates{ false }
{
    _drawableItem.setTextureRect(sf::IntRect{ Geometry::toSfmlRect(_animation.viewRect()) });
    _drawableItem.scale({ 4, 4 });
}

void Player::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
{
    target.draw(_drawableItem, states);
}

void Player::update(float deltatime)
{
    handleMoving(deltatime);

    _drawableItem.setTextureRect(sf::IntRect{ Geometry::toSfmlRect(_animation.viewRect()) });
}

void Player::setPos(PointF position)
{
    _drawableItem.setPosition({ position.x(), position.y() });
}

void Player::setOrigin(Align origin)
{
    _drawableItem.setOrigin(Geometry::toSfmlPoint(localRect().pointBy(origin)));
}

void Player::handleCollision(RectF collisionRect)
{
    if (collisionRect.height() > collisionRect.width())
    {
        // From left
        if (center().x() > collisionRect.pos.x())
            _drawableItem.move({ collisionRect.width(), .0f });
        // From right
        else
            _drawableItem.move({ -collisionRect.width(), .0f });
    }
    else
    {
        // From top
        if (center().y() > collisionRect.pos.y())
            _drawableItem.move({ .0f, collisionRect.height() });
        // From bottom
        else
            _drawableItem.move({ .0f, -collisionRect.height() });
    }
}

PointF Player::center() const
{
    auto pos{ collisionRect().pos };
    float xOffset{ collisionRect().width() / 2 };
    float yOffset{ collisionRect().height() / 2 };
    return { pos.x() + xOffset, pos.y() + yOffset };
}

RectF Player::globalRect() const
{
    return Geometry::toRect(_drawableItem.getGlobalBounds());
}

RectF Player::localRect() const
{
    return Geometry::toRect(_drawableItem.getLocalBounds());
}

RectF Player::collisionRect() const
{
    float widthOffset{ 6.0f };
    float width{ _drawableItem.getGlobalBounds().width - widthOffset };
    float height{ _drawableItem.getGlobalBounds().height / 2 };
    return RectF{ { _drawableItem.getGlobalBounds().left + widthOffset / 2,
                    _drawableItem.getGlobalBounds().top + height },
                  { width, height } };
}

void Player::keyPressEvent(KeyPressEvent *event)
{
    _keyStates[static_cast<size_t>(event->key())] = true;
    _keyboardMode = event->mode();
}

void Player::keyReleaseEvent(KeyReleaseEvent *event)
{
    _keyStates[static_cast<size_t>(event->key())] = false;
    _keyboardMode = event->mode();
}

void Player::handleMoving(float deltaTime)
{
    using Keyboard::Key;
    using Keyboard::Mode;

    size_t textureOffset{ 0 };

    PointF deltaPos{};
    float speed{ 100.0f * deltaTime };

    _animation.setSwitchTime(0.25f);

    if (static_cast<bool>(_keyboardMode & Mode::Shift))
    {
        speed *= 1.5f;
        textureOffset = 4;
        _animation.setSwitchTime(0.15f);
    }

    if (_keyStates[static_cast<size_t>(Key::A)])
    {
        deltaPos.moveX(-1);
        _animation.setRow(textureOffset + 2);
    }
    if (_keyStates[static_cast<size_t>(Key::D)])
    {
        deltaPos.moveX(1);
        _animation.setRow(textureOffset + 3);
    }
    if (_keyStates[static_cast<size_t>(Key::W)])
    {
        deltaPos.moveY(-1);
        _animation.setRow(textureOffset + 1);
    }
    if (_keyStates[static_cast<size_t>(Key::S)])
    {
        deltaPos.moveY(1);
        _animation.setRow(textureOffset + 0);
    }

    if (deltaPos.isDefault())
    {
        _animation.setRow(0);
        _animation.setColumn(1);
        return;
    }
    else if (deltaPos.x() != 0 && deltaPos.y() != 0)
    {
        speed /= sqrt(2);
    }

    _drawableItem.move({ speed * deltaPos.x(), speed * deltaPos.y() });

    _animation.update(deltaTime);
}
} // namespace Scene
