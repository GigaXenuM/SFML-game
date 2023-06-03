#pragma once

#include "SFML/Window/Keyboard.hpp"

namespace Keyboard
{

enum class Key : unsigned long long
{
    A = sf::Keyboard::A,
    D = sf::Keyboard::D,
    S = sf::Keyboard::S,
    W = sf::Keyboard::W,
    Left = sf::Keyboard::Left,
    Right = sf::Keyboard::Right,
    Up = sf::Keyboard::Up,
    Down = sf::Keyboard::Down,
    Space = sf::Keyboard::Space,

    MAX_SIZE = sf::Keyboard::KeyCount
};
} // namespace Keyboard
