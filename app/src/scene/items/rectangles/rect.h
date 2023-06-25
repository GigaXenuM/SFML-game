
#pragma once

#include "scene/items/item.h"

#include "SFML/Graphics/RectangleShape.hpp"

namespace Scene
{

class Rect : public Item
{
public:
    Rect();

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    RectF globalRect() const override;
    RectF localRect() const override;
    PointF center() const override;

    void setPos(PointF position) override;
    void setOrigin(Align origin) override;

private:
    sf::RectangleShape _drawableItem;
};
} // namespace Scene
