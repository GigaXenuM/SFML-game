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

void Scene::draw(sf::RenderTarget *target, const sf::RenderStates *states)
{
    for (auto *item : _graphicsItems)
        target->draw(item->drawableItem(), *states);
}

std::vector<const Item *> Scene::items() const
{
    return _graphicsItems;
}

void Scene::addItem(const Item *item)
{
    _graphicsItems.push_back(item);
}
} // namespace Scene
