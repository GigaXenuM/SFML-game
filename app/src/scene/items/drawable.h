#pragma once

#include "SFML/Graphics/Drawable.hpp"

namespace Scene
{
class Drawable : public sf::Drawable
{
public:
    virtual void update(float /*deltatime*/)
    {
    }
};
} // namespace Scene
