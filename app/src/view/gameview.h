#pragma once

#include "event/eventhandler.h"

#include "geometry/rect.h"

#include <SFML/Graphics/View.hpp>

class GameView : public sf::View, public EventHandler
{
public:
    explicit GameView(RectF rect, EventHandler *parent);

    void mousePressEvent(MousePressEvent *event) override;
    void mouseReleaseEvent(MouseReleaseEvent *event) override;
    void mouseMoveEvent(MouseMoveEvent *event) override;

private:
    bool _canDrag{ false };
};
