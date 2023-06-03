#pragma once

#include "scene/items/collisionitem.h"
#include "scene/items/item.h"

#include "event/keyevents/keyboard.h"
#include "geometry/point.h"

#include <SFML/Graphics/CircleShape.hpp>

#include <array>

class EventHandler;

namespace Scene
{

class Player : public CollisionItem
{
public:
    explicit Player(EventHandler *parent);
    virtual ~Player() = default;

    const sf::Drawable &drawableItem() const override;
    std::optional<RectF> intersects(const Item &item) const override;
    RectF globalRect() const override;
    PointF center() const override;

    void update() override;
    void setPos(PointF position) override;

    void handleCollision(RectF collisionRect) override;

protected:
    void keyPressEvent(KeyPressEvent *event) override;
    void keyReleaseEvent(KeyReleaseEvent *event) override;

private:
    void move();

    sf::CircleShape _drawableItem;
    std::array<bool, static_cast<size_t>(Keyboard::Key::MAX_SIZE)> _keyStates;
};
} // namespace Scene
