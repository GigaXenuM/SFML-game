#pragma once

#include "event/eventhandler.h"

#include <vector>

namespace sf
{
class Drawable;
class RenderTarget;
class RenderStates;
} // namespace sf

namespace Scene
{
class Item;
class CollisionItem;

class Scene : public EventHandler
{
public:
    explicit Scene(EventHandler *parent);
    virtual ~Scene() = default;

    void addItem();

    void render(sf::RenderTarget *target, const sf::RenderStates *states);

    std::vector<Item *> items() const;

    void addItem(Item *item);

    void addToCollisionDetection(CollisionItem *item);

private:
    void detectCollision();

    std::vector<Item *> _graphicsItems;
    std::vector<CollisionItem *> _collisinDetectables;
};

} // namespace Scene
