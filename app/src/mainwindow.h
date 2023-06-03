#pragma once

#include "event/eventhandler.h"
#include "event/mouseevents/mousemoveevent.h"

#include <SFML/Graphics.hpp>

class View;

namespace Scene
{
class Scene;
class Player;
} // namespace Scene

class MainWindow : public sf::RenderWindow, public EventHandler
{
public:
    explicit MainWindow(unsigned int width, unsigned int height, const char *name);
    virtual ~MainWindow();

    int runLoop();

private:
    void handleSfmlEvent(const sf::Event &event);

    Scene::Scene *_scene;
    Scene::Player *_player;
    View *_view;

    MouseMoveEvent _lastMouseMoveEvent;
};
