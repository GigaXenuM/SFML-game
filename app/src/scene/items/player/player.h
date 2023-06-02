#pragma once

#include "scene/items/item.h"

#include <SFML/Graphics/CircleShape.hpp>

class EventHandler;

namespace Scene
{

class Player : public Item
{
public:
    Player(EventHandler *parent);
    virtual ~Player() = default;

    const sf::Drawable &drawableItem() const override;

protected:
    void keyPressEvent(KeyPressEvent *event) override;
    void keyReleaseEvent(KeyReleaseEvent *event) override;

private:
    sf::CircleShape _drawableItem;
};
} // namespace Scene
