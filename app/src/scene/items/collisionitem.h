#pragma once

#include "item.h"

#include "geometry/rect.h"

namespace Scene
{

class CollisionItem : public Item
{
public:
    explicit CollisionItem(EventHandler *parent) : Item{ parent }
    {
    }
    virtual ~CollisionItem() = default;

    virtual void handleCollision(RectF collisionRect) = 0;
};
} // namespace Scene
