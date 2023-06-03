#pragma once

#include "event/eventhandler.h"

#include "geometry/point.h"

#include <SFML/Graphics/Drawable.hpp>

namespace Scene
{

class Item : public EventHandler
{
public:
    explicit Item(EventHandler *parent)
    {
        if (parent != nullptr)
            parent->addEventHandler(this);
    }
    virtual ~Item() = default;

    virtual const sf::Drawable &drawableItem() const = 0;
    virtual void update(){};

    virtual void setPos(PointF position) = 0;
};
} // namespace Scene
