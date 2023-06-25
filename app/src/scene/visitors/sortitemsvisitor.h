#pragma once

#include "visitors/defaultvisitor.h"

#include <memory>

namespace Scene
{
struct ItemContext;

class SortItemsVisitor : public DefaultVisitor
{
public:
    SortItemsVisitor(std::shared_ptr<ItemContext> itemContext);

    void visitSceneItem(Item *item) override;
    void visitSceneCollisionItem(CollisionItem *item) override;
    void visitSceneCollisionHandler(CollisionHandler *item) override;

private:
    std::shared_ptr<ItemContext> _itemContext;
};
} // namespace Scene
