#pragma once

#include "event/eventhandler.h"

#include "geometry/rect.h"

#include <SFML/Graphics/View.hpp>

class View : public sf::View, public EventHandler
{
public:
    explicit View(RectF rect, EventHandler *parent);

    void mousePressEvent(MousePressEvent *event) override;
    void mouseReleaseEvent(MouseReleaseEvent *event) override;
    void mouseMoveEvent(MouseMoveEvent *event) override;

private:
    bool _canDrag{ false };
};
