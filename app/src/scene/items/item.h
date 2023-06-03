#pragma once

#include "SFML/Graphics/Color.hpp"
#include "event/eventhandler.h"

#include "geometry/point.h"
#include "geometry/rect.h"

#include <SFML/Graphics/Drawable.hpp>

#include <optional>

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
    virtual std::optional<RectF> intersects(const Item &item) const = 0;
    virtual RectF globalRect() const = 0;
    virtual PointF center() const = 0;

    virtual void update(){};
    virtual void setPos(PointF position) = 0;
};
} // namespace Scene
