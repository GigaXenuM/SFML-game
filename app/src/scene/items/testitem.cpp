#include "testitem.h"

#include "geometry/utils.h"

#include "SFML/Graphics/RenderTarget.hpp"

namespace Scene
{
TestItem::TestItem() : Item{ nullptr }, _drawableItem{ { 50.0f, 50.0f } }
{
    _drawableItem.setFillColor(sf::Color::Red);
}

void TestItem::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
{
    target.draw(_drawableItem, states);
}

RectF TestItem::globalRect() const
{
    return Geometry::toRect(_drawableItem.getGlobalBounds());
}

RectF TestItem::localRect() const
{
    return Geometry::toRect(_drawableItem.getLocalBounds());
}

RectF TestItem::collisionRect() const
{
    return globalRect();
}

PointF TestItem::center() const
{
    auto sfmlPos{ _drawableItem.getPosition() };
    float xOffset{ _drawableItem.getSize().x / 2 };
    float yOffset{ _drawableItem.getSize().y / 2 };
    return { sfmlPos.x + xOffset, sfmlPos.y + yOffset };
}

void TestItem::setPos(PointF position)
{
    _drawableItem.setPosition({ position.x, position.y });
}

void TestItem::setOrigin(Align origin)
{
    _drawableItem.setOrigin(Geometry::toSfmlPoint(localRect().pointBy(origin)));
}
} // namespace Scene
