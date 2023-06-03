#pragma once

#include "SFML/Graphics/RectangleShape.hpp"
#include "scene/items/item.h"

namespace Scene
{

class TestItem : public Item
{
public:
    TestItem();

    const sf::Drawable &drawableItem() const override;
    std::optional<RectF> intersects(const Item &item) const override;
    RectF globalRect() const override;
    PointF center() const override;

    void setPos(PointF position) override;

private:
    sf::RectangleShape _drawableItem;
};
} // namespace Scene
