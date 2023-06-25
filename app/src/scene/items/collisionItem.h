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

    virtual std::optional<RectF> intersects(const CollisionItem &item) const;

    void accept(IVisitor *visitor) override;
};
} // namespace Scene
