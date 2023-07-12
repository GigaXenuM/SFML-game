#pragma once

#include "drawable.h"
#include "event/eventhandler.h"

#include "geometry/point.h"
#include "geometry/rect.h"

#include <optional>

enum class Align;

using Vertices = std::vector<PointF>;
using Axes = std::vector<PointF>;

namespace Scene
{
class IVisitor;

class Item : public EventHandler, public Drawable
{
public:
    explicit Item(EventHandler *parent);
    virtual ~Item() = default;

    virtual RectF globalRect() const = 0;
    virtual RectF localRect() const = 0;
    virtual PointF center() const = 0;

    virtual void setPos(PointF position) = 0;
    virtual void setOrigin(Align origin) = 0;

    virtual void accept(IVisitor *visitor);
};
} // namespace Scene
