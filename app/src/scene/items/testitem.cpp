#include "testitem.h"

#include "geometry/utils.h"

namespace Scene
{
TestItem::TestItem() : Item{ nullptr }, _drawableItem{ { 50.0f, 50.0f } }
{
    _drawableItem.setFillColor(sf::Color::Red);
}

const sf::Drawable &TestItem::drawableItem() const
{
    return _drawableItem;
}

std::optional<RectF> TestItem::intersects(const Item &item) const
{
    std::optional<sf::FloatRect> sfmlRect{ _drawableItem.getGlobalBounds().findIntersection(
        Geometry::toSfmlRectF(globalRect())) };

    if (sfmlRect.has_value())
        return Geometry::toRectF(sfmlRect.value());

    return std::nullopt;
}

RectF TestItem::globalRect() const
{
    return Geometry::toRectF(_drawableItem.getGlobalBounds());
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
} // namespace Scene
