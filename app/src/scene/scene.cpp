#include "scene.h"

#include "items/item.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

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
}

std::vector<Item *> Scene::items() const
{
    return _graphicsItems;
}

void Scene::addItem(Item *item)
{
    _graphicsItems.push_back(item);
}
} // namespace Scene
