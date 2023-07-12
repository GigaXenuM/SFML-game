#include "rect.h"

#include "geometry/utils.h"

#include "SFML/Graphics/RenderTarget.hpp"

namespace Scene
{
Rect::Rect() : Item{ nullptr }, _drawableItem{ { 50.0f, 50.0f } }
{
    _drawableItem.setFillColor(sf::Color::Yellow);
}

void Rect::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
{
    target.draw(_drawableItem, states);
}

RectF Rect::globalRect() const
{
    return Geometry::toRect(_drawableItem.getGlobalBounds());
}

RectF Rect::localRect() const
{
    return Geometry::toRect(_drawableItem.getLocalBounds());
}

PointF Rect::center() const
{
    const sf::Transform &transform = _drawableItem.getTransform();
    return Geometry::toPoint(transform.transformPoint(_drawableItem.getGeometricCenter()));
}

void Rect::setPos(PointF position)
{
    _drawableItem.setPosition({ position.x(), position.y() });
}

void Rect::setOrigin(Align origin)
{
    _drawableItem.setOrigin(Geometry::toSfmlPoint(localRect().pointBy(origin)));
}
} // namespace Scene
