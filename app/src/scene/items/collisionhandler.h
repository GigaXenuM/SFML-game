#pragma once

#include "scene/items/collisionitem.h"

#include "visitors/ivisitor.h"

namespace Scene
{

class CollisionHandler : public CollisionItem
{
public:
    explicit CollisionHandler(EventHandler *parent) : CollisionItem{ parent }
    {
    }
    virtual ~CollisionHandler() = default;

    virtual void handleCollision(const CollisionItem *item) = 0;

    void accept(IVisitor *visitor) override
    {
        visitor->visitSceneCollisionHandler(this);
    };
};
} // namespace Scene
