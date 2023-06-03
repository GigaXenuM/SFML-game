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

class Scene : public EventHandler
{
public:
    explicit Scene(EventHandler *parent);
    virtual ~Scene() = default;

    void addItem();

    void render(sf::RenderTarget *target, const sf::RenderStates *states);

    std::vector<Item *> items() const;

    void addItem(Item *item);

private:
    std::vector<Item *> _graphicsItems;
};

} // namespace Scene
