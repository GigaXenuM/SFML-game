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

    void setPos(PointF position) override;

private:
    sf::RectangleShape _drawableItem;
};
} // namespace Scene
