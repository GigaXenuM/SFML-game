#pragma once

#include "scene/items/collisionitem.h"

#include "SFML/Graphics/RectangleShape.hpp"

namespace Scene
{

class CollisionRect : public CollisionItem
{
public:
    CollisionRect();

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    RectF globalRect() const override;
    RectF localRect() const override;
    RectF collisionRect() const override;
    PointF center() const override;

    void setPos(PointF position) override;
    void setOrigin(Align origin) override;

private:
    sf::RectangleShape _drawableItem;
};
} // namespace Scene
