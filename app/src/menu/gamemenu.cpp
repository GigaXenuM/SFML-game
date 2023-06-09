#include "gamemenu.h"

#include "scene/items/button/textbutton.h"

#include "SFML/Graphics/RenderTarget.hpp"

#include <iostream>

GameMenu::GameMenu(EventHandler *eventHandler) : _eventHandler{ eventHandler }
{
    sf::Font font;
    bool successLoad{ font.loadFromFile("res/fonts/arial.ttf") };
    if (!successLoad)
        std::cerr << "GameMenu: Failed load font." << std::endl;

    auto button{ std::make_shared<Scene::TextButton>("Button", font, SizeF{ 100.0f, 50.0f },
                                                     _eventHandler) };
    button->setPos({ 150, 280 });
    button->onClick([]() { std::cout << "Button clicked!" << std::endl; });

    _buttons.push_back(button);
}

void GameMenu::render(sf::RenderTarget &target, const sf::RenderStates &states)
{
    target.clear(sf::Color(0, 0, 0, 255));

    for (const auto &button : _buttons)
        target.draw(*button, states);
}
