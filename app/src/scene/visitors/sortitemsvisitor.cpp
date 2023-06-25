#include "sortitemsvisitor.h"

#include "itemcontext.h"

namespace Scene
{
SortItemsVisitor::SortItemsVisitor(std::shared_ptr<ItemContext> itemContext)
    : _itemContext{ std::move(itemContext) }
{
}

void SortItemsVisitor::visitSceneItem(Item *item)
{
    _itemContext->items.push_back(item);
}

void SortItemsVisitor::visitSceneCollisionItem(CollisionItem *item)
{
    _itemContext->collisionItems.push_back(item);
}

void SortItemsVisitor::visitSceneCollisionHandler(CollisionHandler *item)
{
    _itemContext->collisionHandlers.push_back(item);
}
} // namespace Scene
