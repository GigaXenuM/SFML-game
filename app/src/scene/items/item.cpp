#include "item.h"

#include "geometry/utils.h"

#include <SFML/Graphics/Rect.hpp>

namespace Scene
{

std::optional<RectF> Item::intersects(const Item &item) const
{
    std::optional<sf::FloatRect> sfmlRect{ Geometry::toSfmlRect(collisionRect())
                                               .findIntersection(
                                                   Geometry::toSfmlRect(item.collisionRect())) };

    if (sfmlRect.has_value())
        return Geometry::toRect(sfmlRect.value());

    return std::nullopt;
}

} // namespace Scene
