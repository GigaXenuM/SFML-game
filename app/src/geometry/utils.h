#pragma once

#include "point.h"
#include "rect.h"
#include "size.h"

#include "SFML/Graphics/Rect.hpp"

namespace Geometry
{
RectF toRectF(sf::FloatRect rect);
sf::FloatRect toSfmlRectF(RectF rect);

PointF toPointF(sf::Vector2f point);
sf::Vector2f toSfmlPointF(PointF point);

SizeF toSizeF(sf::Vector2f size);
sf::Vector2f toSfmlSizeF(SizeF size);

double distance(PointF p1, PointF p2);
} // namespace Geometry
