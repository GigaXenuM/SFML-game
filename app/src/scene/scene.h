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
    Scene(EventHandler *parent);
    virtual ~Scene() = default;

    void addItem();

    void draw(sf::RenderTarget *target, const sf::RenderStates *states);

    std::vector<const Item *> items() const;

    void addItem(const Item *item);

private:
    std::vector<const Item *> _graphicsItems;
};

} // namespace Scene
