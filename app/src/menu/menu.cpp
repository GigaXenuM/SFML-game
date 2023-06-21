#include "menu.h"

#include "geometry/utils.h"
#include "layout/verticallayout.h"
#include "scene/items/item.h"

#include "SFML/Graphics/RenderTarget.hpp"

Menu::Menu(sf::RenderTarget *renderTarget, EventHandler *eventHandler)
    : _renderTarget{ renderTarget },
      _layout{ std::make_shared<VerticalLayout>(
          static_cast<RectF>(Geometry::toRect(renderTarget->getViewport(renderTarget->getView()))),
          eventHandler) },
      _eventHandler{ eventHandler }
{
}

void Menu::render(float /*deltatime*/)
{
    _renderTarget->clear(sf::Color(0, 0, 0, 255));

    for (const auto &item : _layout->items())
        _renderTarget->draw(*item);
}

void Menu::setLayout(std::shared_ptr<Layout> layout)
{
    _layout = layout;
}

void Menu::addItem(std::shared_ptr<Scene::Item> item)
{
    _layout->addItem(item);
}
