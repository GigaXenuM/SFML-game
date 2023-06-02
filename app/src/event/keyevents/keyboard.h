#pragma once

#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"

namespace Keyboard
{

enum class Key
{
    A = sf::Keyboard::A,
    D = sf::Keyboard::D,
    S = sf::Keyboard::S,
    W = sf::Keyboard::W,
    Space = sf::Keyboard::Space
};

enum class Actions
{
    Pressed = sf::Event::KeyPressed,
    Released = sf::Event::KeyReleased
};
} // namespace Keyboard
