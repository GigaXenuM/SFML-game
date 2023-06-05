#pragma once

#include "scene/animation/animation.h"
#include "scene/items/collisionitem.h"
#include "scene/items/item.h"

#include "event/keyevents/keyboard.h"
#include "geometry/point.h"

#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <array>
#include <memory>

class EventHandler;

namespace Scene
{

class Player : public CollisionItem
{
public:
    explicit Player(std::shared_ptr<sf::Texture> texture, EventHandler *parent);
    virtual ~Player() = default;

    const sf::Drawable &drawableItem() const override;
    RectF globalRect() const override;
    RectF collisionRect() const override;
    PointF center() const override;

    void update() override;
    void setPos(PointF position) override;

    void handleCollision(RectF collisionRect) override;

protected:
    void keyPressEvent(KeyPressEvent *event) override;
    void keyReleaseEvent(KeyReleaseEvent *event) override;

private:
    bool isMoved();
    void handleMoving();

    std::shared_ptr<sf::Texture> _texture;
    sf::Sprite _drawableItem;

    Animation _animation;
    std::array<bool, static_cast<size_t>(Keyboard::Key::MAX_SIZE)> _keyStates;
    Keyboard::Mode _keyboardMode;

    sf::Clock _clock;
};
} // namespace Scene
