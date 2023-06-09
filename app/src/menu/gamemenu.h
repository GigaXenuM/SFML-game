#pragma once

#include "irenderer.h"

#include <memory>
#include <vector>

class EventHandler;

namespace sf
{
class Drawable;
} // namespace sf

class GameMenu : public IRenderer
{
public:
    GameMenu(EventHandler *eventHandler);

    void render(sf::RenderTarget &target, const sf::RenderStates &states) override;

private:
    std::vector<std::shared_ptr<sf::Drawable>> _buttons;

    EventHandler *_eventHandler;
};
