#pragma once

#include "event/eventhandler.h"

#include <SFML/Graphics/View.hpp>

template <typename T> struct Rect;

class MenuView : public sf::View, public EventHandler
{
    using RectF = Rect<float>;

public:
    explicit MenuView(RectF rect, EventHandler *parent);
};
