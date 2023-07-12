#include "collisionrect.h"

#include "geometry/utils.h"

#include "SFML/Graphics/RenderTarget.hpp"

namespace Scene
{
CollisionRect::CollisionRect() : CollisionItem{ nullptr }, _drawableItem{ { 50.0f, 50.0f } }
{
    _drawableItem.setFillColor(sf::Color::Red);
    _drawableItem.rotate(sf::degrees(45.0f));
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
    const sf::Transform &transform = _drawableItem.getTransform();
    return Geometry::toPoint(transform.transformPoint(_drawableItem.getGeometricCenter()));
}

PointF CollisionRect::collisionCenter() const
{
    return center();
}

Vertices CollisionRect::vertices() const
{
    Vertices vertices;
    const sf::Transform &transform = _drawableItem.getTransform();
    for (std::size_t i = 0u; i < _drawableItem.getPointCount(); ++i)
        vertices.push_back(Geometry::toPoint(transform.transformPoint(_drawableItem.getPoint(i))));

    return vertices;
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
