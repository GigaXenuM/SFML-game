#include "testitem.h"
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

void TestItem::setPos(PointF position)
{
    _drawableItem.setPosition({ position.x, position.y });
}
} // namespace Scene
