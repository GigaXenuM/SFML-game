#include "scene.h"

#include "items/collisionitem.h"

#include "items/item.h"

#include "geometry/utils.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <iterator>

namespace Scene
{
Scene::Scene(EventHandler *parent)
{
    if (parent != nullptr)
        parent->addEventHandler(this);
}

void Scene::render(sf::RenderTarget &target, const sf::RenderStates &states)
{
    target.clear(sf::Color(87, 179, 113, 255));

    for (const auto &item : _graphicsItems)
    {
        item->update();
        target.draw(*item, states);
    }

    detectCollision();
}

std::vector<std::shared_ptr<Item>> Scene::items() const
{
    return _graphicsItems;
}

void Scene::addItem(std::shared_ptr<Item> item)
{
    _graphicsItems.push_back(item);
}

void Scene::addToCollisionDetection(std::shared_ptr<CollisionItem> item)
{
    _collisinDetectables.push_back(item);
}

void Scene::detectCollision()
{
    for (const auto &detectable : _collisinDetectables)
    {
        std::vector<std::shared_ptr<Item>> itemsToDetectCollision;
        std::copy_if(_graphicsItems.begin(), _graphicsItems.end(),
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

void Scene::handleCollision(std::shared_ptr<CollisionItem> collisionItem,
                            const std::vector<std::shared_ptr<Item>> &items)
{
    for (const auto &item : items)
    {
        auto collisionRect{ collisionItem->intersects(*item) };
        if (collisionRect.has_value())
            collisionItem->handleCollision(collisionRect.value());
    }
}
} // namespace Scene
