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
    setupSprite();
    setupCollision();
}

void Player::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
{
    target.draw(_drawableItem, states);
}

void Player::update(float deltatime)
{
    handleMoving(deltatime);
    updateTexture();
}

void Player::setPos(PointF position)
{
    _drawableItem.setPosition({ position.x(), position.y() });
    updateCollision();
}

void Player::setOrigin(Align origin)
{
    _drawableItem.setOrigin(Geometry::toSfmlPoint(localRect().pointBy(origin)));
}

void Player::handleCollision(const CollisionItem *item)
{
    Axes currentAxes{ axes() };
    Axes itemAxes{ item->axes() };

    Axes axes{};
    axes.reserve(currentAxes.size() + itemAxes.size());
    axes.insert(axes.end(), currentAxes.begin(), currentAxes.end());
    axes.insert(axes.end(), itemAxes.begin(), itemAxes.end());

    VectorF offset{ 0, 0 };

    float minOverlap = std::numeric_limits<float>::infinity();

    for (auto &axis : axes)
    {
        const VectorF currentProjection = projectionOn(axis);
        const VectorF otherProjection = item->projectionOn(axis);

        if (!currentProjection.overlap(otherProjection))
            return;

        float overlap = currentProjection.overlapLength(otherProjection);

        if (overlap < minOverlap)
        {
            minOverlap = overlap;
            offset = axis * minOverlap;
        }
    }

    const VectorF beetweenCenters{ collisionCenter() - item->collisionCenter() };
    const bool needReflect = beetweenCenters.dot(offset) < 0;
    if (needReflect)
        offset = -offset;

    move(offset);
}

PointF Player::center() const
{
    return globalRect().center();
}

PointF Player::collisionCenter() const
{
    const sf::Transform &transform = _collisionItem.getTransform();
    return Geometry::toPoint(transform.transformPoint(_collisionItem.getGeometricCenter()));
}

Vertices Player::vertices() const
{
    Vertices vertices;
    const sf::Transform &transform = _collisionItem.getTransform();
    for (std::size_t i = 0u; i < _collisionItem.getPointCount(); ++i)
        vertices.push_back(Geometry::toPoint(transform.transformPoint(_collisionItem.getPoint(i))));

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
    return Geometry::toRect(_collisionItem.getGlobalBounds());
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

void Player::setupSprite()
{
    updateTexture();
    _drawableItem.scale({ 4, 4 });
}

void Player::setupCollision()
{
    RectF rect{ Geometry::toRect(_drawableItem.getGlobalBounds()) };
    _collisionItem.setSize({ rect.height() / 2 - 10, rect.height() / 2 });

    RectF collision{ Geometry::toRect(_collisionItem.getGlobalBounds()) };
    PointF collisionOrigin{ collision.pointBy(Align::Bottom) + PointF{ 0.0f, 5.0f } };
    _collisionItem.setOrigin(collisionOrigin.data());

    updateCollision();
}

void Player::updateTexture()
{
    _drawableItem.setTextureRect(sf::IntRect{ Geometry::toSfmlRect(_animation.viewRect()) });
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

    move(deltaPos * speed);

    _animation.update(deltaTime);
}

void Player::move(VectorF offset)
{
    _drawableItem.move(offset.data());
    updateCollision();
}

void Player::updateCollision()
{
    _collisionItem.setPosition(globalRect().pointBy(Align::Bottom).data());
}
} // namespace Scene
