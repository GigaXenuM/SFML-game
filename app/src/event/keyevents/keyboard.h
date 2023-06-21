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
    F = sf::Keyboard::F,
    Left = sf::Keyboard::Left,
    Right = sf::Keyboard::Right,
    Up = sf::Keyboard::Up,
    Down = sf::Keyboard::Down,
    Space = sf::Keyboard::Space,
    Escape = sf::Keyboard::Escape,

    MAX_SIZE = sf::Keyboard::KeyCount
};

enum class Mode : unsigned long long
{
    None = 0,

    Shift = 1,
    Alt = 2,
    Control = 4,

    MAX_SIZE = Control
};

inline Mode operator|(Mode a, Mode b)
{
    return static_cast<Mode>(static_cast<int>(a) | static_cast<int>(b));
}

inline Mode operator&(Mode a, Mode b)
{
    return static_cast<Mode>(static_cast<int>(a) & static_cast<int>(b));
}

inline Mode &operator|=(Mode &a, Mode b)
{
    return a = a | b;
}
} // namespace Keyboard
