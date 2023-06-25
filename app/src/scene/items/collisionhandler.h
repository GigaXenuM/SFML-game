#pragma once

#include "scene/items/collisionitem.h"

#include "visitors/ivisitor.h"

#include "geometry/rect.h"

namespace Scene
{

class CollisionHandler : public CollisionItem
{
public:
    explicit CollisionHandler(EventHandler *parent) : CollisionItem{ parent }
    {
    }
    virtual ~CollisionHandler() = default;

    virtual void handleCollision(RectF collisionRect) = 0;

    void accept(IVisitor *visitor) override
    {
        visitor->visitSceneCollisionHandler(this);
    };
};
} // namespace Scene
