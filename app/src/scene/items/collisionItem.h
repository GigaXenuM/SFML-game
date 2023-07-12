#pragma once

#include "item.h"

namespace Scene
{

class CollisionItem : public Item
{
public:
    CollisionItem(EventHandler *parent) : Item{ parent }
    {
    }

    virtual RectF collisionRect() const = 0;
    virtual Vertices vertices() const = 0;

    VectorF projectionOn(VectorF axis) const;
    Axes axes() const;

    void accept(IVisitor *visitor) override;
};
} // namespace Scene
