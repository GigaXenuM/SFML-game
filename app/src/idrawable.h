#pragma once

namespace sf
{
class Drawable;
} // namespace sf

class IDrawable
{
public:
    virtual const sf::Drawable &drawableItem() const = 0;
};
