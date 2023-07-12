#include "scene.h"

#include "itemcontext.h"
#include "items/collisionhandler.h"
#include "items/item.h"

#include "geometry/utils.h"

#include "visitors/sortitemsvisitor.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <iterator>

namespace Scene
{
Scene::Scene(sf::RenderTarget *renderTarget, EventHandler *parent)
    : _renderTarget{ renderTarget }, _itemContext{ std::make_shared<ItemContext>() }
{
    if (parent != nullptr)
        parent->addEventHandler(this);
}

void Scene::render(float deltatime)
{
    _renderTarget->clear(sf::Color(87, 179, 113, 255));

    for (const auto &item : _itemsToDrawing)
    {
        item->update(deltatime);
        _renderTarget->draw(*item);
    }

    detectCollision();
}

void Scene::addItem(Item *item)
{
    SortItemsVisitor visitor{ _itemContext };
    item->accept(&visitor);

    _itemsToDrawing.push_back(item);
}

void Scene::detectCollisionFor(CollisionHandler *item)
{
    _itemContext->collisionHandlers.push_back(item);
}

void Scene::detectCollision()
{
    for (const auto &detectable : _itemContext->collisionHandlers)
    {
        std::vector<CollisionItem *> itemsToDetectCollision;
        std::copy_if(_itemContext->collisionItems.begin(), _itemContext->collisionItems.end(),
                     std::back_inserter(itemsToDetectCollision),
                     [detectable](auto item)
                     {
                         const bool condition1{ item != detectable };
                         const bool condition2{
                             Geometry::distance(detectable->center(), item->center()) < 200.0
                         };
                         return condition1 && condition2;
                     });

        handleCollision(detectable, itemsToDetectCollision);
    }
}

void Scene::handleCollision(CollisionHandler *collisionHandler,
                            const std::vector<CollisionItem *> &collisionItems)
{
    for (const auto &collisionItem : collisionItems)
    {
        collisionHandler->handleCollision(collisionItem);
    }
}
} // namespace Scene
