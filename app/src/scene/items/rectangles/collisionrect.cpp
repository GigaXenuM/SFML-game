#include "collisionrect.h"

#include "geometry/utils.h"

#include "SFML/Graphics/RenderTarget.hpp"

namespace Scene
{
CollisionRect::CollisionRect() : CollisionItem{ nullptr }, _drawableItem{ { 50.0f, 50.0f } }
{
    _drawableItem.setFillColor(sf::Color::Red);
}

void CollisionRect::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
{
    target.draw(_drawableItem, states);
}

RectF CollisionRect::globalRect() const
{
    return Geometry::toRect(_drawableItem.getGlobalBounds());
}

RectF CollisionRect::localRect() const
{
    return Geometry::toRect(_drawableItem.getLocalBounds());
}

RectF CollisionRect::collisionRect() const
{
    return globalRect();
}

PointF CollisionRect::center() const
{
    auto sfmlPos{ _drawableItem.getPosition() };
    float xOffset{ _drawableItem.getSize().x / 2 };
    float yOffset{ _drawableItem.getSize().y / 2 };
    return { sfmlPos.x + xOffset, sfmlPos.y + yOffset };
}

void CollisionRect::setPos(PointF position)
{
    _drawableItem.setPosition({ position.x(), position.y() });
}

void CollisionRect::setOrigin(Align origin)
{
    _drawableItem.setOrigin(Geometry::toSfmlPoint(localRect().pointBy(origin)));
}
} // namespace Scene
