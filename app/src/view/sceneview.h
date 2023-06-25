#pragma once

#include "event/eventhandler.h"
#include "view/iview.h"

#include <SFML/Graphics/View.hpp>

#include <memory>

template <typename T> struct Rect;

namespace Scene
{
class Item;
}

namespace sf
{
class RenderTarget;
} // namespace sf

class SceneView : public IView, public EventHandler, public sf::View
{
    using RectF = Rect<float>;

public:
    explicit SceneView(sf::RenderTarget *renderTarget, RectF rect, EventHandler *parent);

    void update(float deltaTime) override;

    void keyPressEvent(KeyPressEvent *event) override;
    void mousePressEvent(MousePressEvent *event) override;
    void mouseReleaseEvent(MouseReleaseEvent *event) override;
    void mouseMoveEvent(MouseMoveEvent *event) override;

    void center(float deltaTime);

    void setCenterTarget(Scene::Item *centerTarget);

private:
    sf::RenderTarget *_renderTarget;

    Scene::Item *_centerTarget;

    bool _canDrag{ false };
    bool _needCenter{ false };

    float _speedCentering;
};
