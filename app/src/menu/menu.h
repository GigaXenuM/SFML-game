#pragma once

#include "irenderer.h"

#include <memory>
#include <vector>

class EventHandler;

class Layout;

namespace sf
{
class Drawable;
} // namespace sf

namespace Scene
{
class Item;
} // namespace Scene

class Menu : public IRenderer
{
public:
    explicit Menu(sf::RenderTarget *renderTarget, EventHandler *eventHandler);

    void render(float deltatime) override;

    void setLayout(std::shared_ptr<Layout> layout);

    void addItem(std::shared_ptr<Scene::Item> item);

private:
    sf::RenderTarget *_renderTarget;
    std::shared_ptr<Layout> _layout;

    EventHandler *_eventHandler;
};
