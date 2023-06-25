#include "sceneview.h"

#include "event/keyevents/keypressevent.h"
#include "event/mouseevents/mousemoveevent.h"
#include "event/mouseevents/mousepressevent.h"
#include "event/mouseevents/mousereleaseevent.h"

#include "geometry/rect.h"
#include "geometry/utils.h"

#include "scene/items/item.h"

#include "SFML/Graphics/RenderTarget.hpp"

SceneView::SceneView(sf::RenderTarget *renderTarget, RectF rect, EventHandler *parent)
    : sf::View{ { rect.pos.x, rect.pos.y }, { rect.size.width, rect.size.height } },
      _renderTarget{ renderTarget },
      _speedCentering{ 2.0f }
{
    if (parent != nullptr)
        parent->addEventHandler(this);
}

void SceneView::update(float deltaTime)
{
    if (_needCenter)
        center(deltaTime);

    _renderTarget->setView(*this);
}

void SceneView::keyPressEvent(KeyPressEvent *event)
{
    if (event->key() == Keyboard::Key::F)
        _needCenter = true;
}

void SceneView::mousePressEvent(MousePressEvent *event)
{
    if (event->button() == Mouse::Button::Middle)
        _canDrag = true;
}

void SceneView::mouseReleaseEvent(MouseReleaseEvent *event)
{
    if (event->button() == Mouse::Button::Middle)
        _canDrag = false;
}

void SceneView::mouseMoveEvent(MouseMoveEvent *event)
{
    if (!_canDrag)
        return;

    PointF delta{ event->lastPosition() - event->position() };
    move(Geometry::toSfmlPoint(delta));

    _needCenter = false;
}

void SceneView::center(float deltaTime)
{
    PointF viewCenter{ Geometry::toPoint(getCenter()) };
    PointF targetCenter{ _centerTarget->center() };

    PointF delta{ targetCenter - viewCenter };

    if (viewCenter != targetCenter)
    {
        move(Geometry::toSfmlPoint(delta * _speedCentering * deltaTime));
    }
}

void SceneView::setCenterTarget(Scene::Item *centerTarget)
{
    _centerTarget = centerTarget;
    _needCenter = true;
}
