#pragma once

namespace Scene
{

class Item;
class CollisionItem;
class CollisionHandler;

class IVisitor
{
public:
    ~IVisitor() = default;

    virtual void visitSceneItem(Item *item) = 0;
    virtual void visitSceneCollisionItem(CollisionItem *item) = 0;
    virtual void visitSceneCollisionHandler(CollisionHandler *item) = 0;
};

} // namespace Scene
