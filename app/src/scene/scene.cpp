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

void Scene::render(sf::RenderTarget *target, const sf::RenderStates *states)
{
    for (auto *item : _graphicsItems)
    {
        item->update();
        target->draw(item->drawableItem(), *states);
    }

    detectCollision();
}

std::vector<Item *> Scene::items() const
{
    return _graphicsItems;
}

void Scene::addItem(Item *item)
{
    _graphicsItems.push_back(item);
}

void Scene::addToCollisionDetection(CollisionItem *item)
{
    _collisinDetectables.push_back(item);
}

void Scene::detectCollision()
{
    for (auto *detectable : _collisinDetectables)
    {
        std::vector<Item *> itemsToDetectCollision;
        std::copy_if(_graphicsItems.begin(), _graphicsItems.end(),
                     std::back_inserter(itemsToDetectCollision),
                     [detectable](Item *item)
                     {
                         const bool condition1{ item != detectable };
                         const bool condition2{
                             Geometry::distance(detectable->center(), item->center()) < 200.0
                         };
                         return condition1 && condition2;
                     });

        for (auto *item : itemsToDetectCollision)
        {
            auto collisionRect{ detectable->intersects(*item) };
            if (collisionRect.has_value())
                detectable->handleCollision(collisionRect.value());
        }
    }
}
} // namespace Scene
