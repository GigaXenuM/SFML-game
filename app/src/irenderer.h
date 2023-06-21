#pragma once

namespace sf
{
class RenderTarget;
class RenderStates;
} // namespace sf

class IRenderer
{
public:
    virtual void render(float deltatime) = 0;
};
