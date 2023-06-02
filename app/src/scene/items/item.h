#pragma once

#include "event/eventhandler.h"

#include <SFML/Graphics/Drawable.hpp>

namespace Scene
{

class Item : public EventHandler
{
public:
    Item(EventHandler *parent)
    {
        if (parent != nullptr)
            parent->addEventHandler(this);
    }
    virtual ~Item() = default;

    virtual const sf::Drawable &drawableItem() const = 0;
};
} // namespace Scene
