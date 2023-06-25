#pragma once

#include <memory>
#include <vector>

namespace Scene
{
class Item;
class CollisionItem;
class CollisionHandler;

struct ItemContext
{
    std::vector<Item *> items;
    std::vector<CollisionItem *> collisionItems;
    std::vector<CollisionHandler *> collisionHandlers;
};
} // namespace Scene
