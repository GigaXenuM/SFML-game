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

class Scene : public EventHandler, public IRenderer
{
public:
    explicit Scene(sf::RenderTarget *renderTarget, EventHandler *parent);
    virtual ~Scene() = default;

    void addItem();

    void render(float deltatime) override;

    std::vector<std::shared_ptr<Item>> items() const;

    void addItem(std::shared_ptr<Item> item);

    void addToCollisionDetection(std::shared_ptr<CollisionItem> item);

private:
    void detectCollision();
    void handleCollision(std::shared_ptr<CollisionItem> collisionItem,
                         const std::vector<std::shared_ptr<Item>> &items);

    sf::RenderTarget *_renderTarget{ nullptr };
    std::vector<std::shared_ptr<Item>> _graphicsItems;
    std::vector<std::shared_ptr<CollisionItem>> _collisinDetectables;
};

} // namespace Scene
