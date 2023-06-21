#pragma once

#include "event/eventhandler.h"

#include "geometry/point.h"
#include "geometry/rect.h"

#include "SFML/Graphics/Drawable.hpp"

#include <optional>

enum class Align;

namespace Scene
{

class Item : public EventHandler, public sf::Drawable
{
public:
    explicit Item(EventHandler *parent)
    {
        if (parent != nullptr)
            parent->addEventHandler(this);
    }
    virtual ~Item() = default;

    virtual RectF globalRect() const = 0;
    virtual RectF localRect() const = 0;
    virtual RectF collisionRect() const = 0;
    virtual PointF center() const = 0;

    virtual std::optional<RectF> intersects(const Item &item) const;

    virtual void update(float /*deltatime*/){};
    virtual void setPos(PointF position) = 0;
    virtual void setOrigin(Align origin) = 0;
};
} // namespace Scene
