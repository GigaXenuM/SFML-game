#pragma once

namespace sf
{
class RenderTarget;
class RenderStates;
} // namespace sf

class IRenderer
{
public:
    virtual void render(sf::RenderTarget &target, const sf::RenderStates &states) = 0;
};
