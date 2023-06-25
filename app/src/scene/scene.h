#pragma once

#include "event/eventhandler.h"
#include "irenderer.h"

#include <memory>
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
class CollisionHandler;
struct ItemContext;
class Drawable;

class Scene : public EventHandler, public IRenderer
{
public:
    explicit Scene(sf::RenderTarget *renderTarget, EventHandler *parent);
    virtual ~Scene() = default;

    void addItem();

    void render(float deltatime) override;

    void addItem(Item *item);

    void detectCollisionFor(CollisionHandler *item);

private:
    void detectCollision();
    void handleCollision(CollisionHandler *collisionHandler,
                         const std::vector<CollisionItem *> &collisionItems);

    sf::RenderTarget *_renderTarget{ nullptr };
    std::shared_ptr<ItemContext> _itemContext;
    std::vector<Drawable *> _itemsToDrawing;
};

} // namespace Scene
