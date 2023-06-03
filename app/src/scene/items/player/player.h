#pragma once

#include "scene/items/item.h"

#include "event/keyevents/keyboard.h"
#include "geometry/point.h"

#include <SFML/Graphics/CircleShape.hpp>

#include <array>

class EventHandler;

namespace Scene
{

class Player : public Item
{
public:
    explicit Player(EventHandler *parent);
    virtual ~Player() = default;

    const sf::Drawable &drawableItem() const override;

    void update() override;

    void setPos(PointF position) override;
    PointF position() const;

protected:
    void keyPressEvent(KeyPressEvent *event) override;
    void keyReleaseEvent(KeyReleaseEvent *event) override;

private:
    void move();

    sf::CircleShape _drawableItem;
    std::array<bool, static_cast<size_t>(Keyboard::Key::MAX_SIZE)> _keyStates;
};
} // namespace Scene
