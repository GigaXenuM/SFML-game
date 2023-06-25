#include "collisionitem.h"

#include "utils.h"

#include "visitors/ivisitor.h"

#include "SFML/Graphics/Rect.hpp"

namespace Scene
{

std::optional<RectF> CollisionItem::intersects(const CollisionItem &item) const
{
    std::optional<sf::FloatRect> sfmlRect{ Geometry::toSfmlRect(collisionRect())
                                               .findIntersection(
                                                   Geometry::toSfmlRect(item.collisionRect())) };

    if (sfmlRect.has_value())
        return Geometry::toRect(sfmlRect.value());

    return std::nullopt;
}

void CollisionItem::accept(IVisitor *visitor)
{
    visitor->visitSceneCollisionItem(this);
}
} // namespace Scene
