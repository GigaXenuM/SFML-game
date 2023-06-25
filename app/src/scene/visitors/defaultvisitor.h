#pragma once

#include "visitors/ivisitor.h"

namespace Scene
{

class DefaultVisitor : public IVisitor
{
public:
    DefaultVisitor() = default;

    virtual void visitSceneItem(Item *item) override;
    virtual void visitSceneCollisionItem(CollisionItem *item) override;
    virtual void visitSceneCollisionHandler(CollisionHandler *item) override;
};
} // namespace Scene
