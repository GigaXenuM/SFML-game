#include "utils.h"

#include <cmath>

namespace Geometry
{

RectF toRectF(sf::FloatRect rect)
{
    return RectF{ toPointF(rect.getPosition()), toSizeF(rect.getSize()) };
}

sf::FloatRect toSfmlRectF(RectF rect)
{
    return sf::FloatRect{ toSfmlPointF(rect.pos), toSfmlSizeF(rect.size) };
}

PointF toPointF(sf::Vector2f point)
{
    return PointF{ point.x, point.y };
}

sf::Vector2f toSfmlPointF(PointF point)
{
    return sf::Vector2f{ point.x, point.y };
}

SizeF toSizeF(sf::Vector2f size)
{
    return SizeF{ size.x, size.y };
}

sf::Vector2f toSfmlSizeF(SizeF size)
{
    return sf::Vector2f{ size.width, size.height };
}

double distance(PointF p1, PointF p2)
{
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

} // namespace Geometry
