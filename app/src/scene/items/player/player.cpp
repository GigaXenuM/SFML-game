#include "player.h"

#include "event/keyevents/keyboard.h"
#include "event/keyevents/keypressevent.h"
#include "event/keyevents/keyreleaseevent.h"

#include "geometry/utils.h"

#include "SFML/Graphics/RenderTarget.hpp"

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

void Player::handleCollision(const CollisionItem *item)
{
    Axes currentAxes = axes();
    Axes axes2 = item->axes();

    VectorF mtv{ 0, 0 };

    std::transform(axes2.cbegin(), axes2.cend(), std::back_inserter(currentAxes),
                   [](const VectorF vec) { return vec; });

    // we need to find the minimal overlap and axis on which it happens
    float minOverlap = std::numeric_limits<float>::infinity();

    for (auto &axis : currentAxes)
    {
        VectorF proj1 = projectionOn(axis);
        VectorF proj2 = item->projectionOn(axis);

        if (!proj1.overlap(proj2))
            return;

        float overlap = proj1.overlapLength(proj2);

        if (overlap < minOverlap)
        {
            minOverlap = overlap;
            mtv = axis * minOverlap;
        }
    }

    VectorF beetweenCenters{ center() - item->center() };
    bool notPointingInTheSameDirection = beetweenCenters.dot(mtv) < 0;
    if (notPointingInTheSameDirection)
        mtv = -mtv;

    _drawableItem.move({ mtv.x(), mtv.y() });
}

PointF Player::center() const
{
    auto pos{ collisionRect().pos };
    float xOffset{ collisionRect().width() / 2 };
    float yOffset{ collisionRect().height() / 2 };
    return { pos.x() + xOffset, pos.y() + yOffset };
}

Vertices Player::vertices() const
{
    sf::RectangleShape shape{ _drawableItem.getLocalBounds().getSize() };
    shape.setPosition(_drawableItem.getPosition());

    Vertices vertices;
    const sf::Transform &transform = _drawableItem.getTransform();
    for (std::size_t i = 0u; i < shape.getPointCount(); ++i)
        vertices.push_back(Geometry::toPoint(transform.transformPoint(shape.getPoint(i))));

    return vertices;
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
