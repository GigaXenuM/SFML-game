#pragma once

#include "event/eventhandler.h"

#include <SFML/Graphics.hpp>

namespace Scene
{
class Scene;
class Player;
} // namespace Scene

class MainWindow : public sf::RenderWindow, public EventHandler
{
public:
    MainWindow(unsigned int width, unsigned int height, const char *name);
    virtual ~MainWindow();

    int runLoop();

private:
    Scene::Scene *_scene;
    Scene::Player *_player;
};
