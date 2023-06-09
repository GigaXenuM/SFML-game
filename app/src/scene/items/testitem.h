#pragma once

#include "scene/items/item.h"

#include "SFML/Graphics/RectangleShape.hpp"

namespace Scene
{

class TestItem : public Item
{
public:
    TestItem();

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    RectF globalRect() const override;
    RectF collisionRect() const override;
    PointF center() const override;

    void setPos(PointF position) override;

private:
    sf::RectangleShape _drawableItem;
};
} // namespace Scene
