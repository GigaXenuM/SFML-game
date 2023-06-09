#pragma once

#include "event/eventhandler.h"
#include "event/mouseevents/mousemoveevent.h"

#include <SFML/Graphics.hpp>

class GameMenu;
class MenuView;
class GameView;

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

    int gameLoop();

private:
    void handleSfmlEvent(const sf::Event &event);

    void composeMenu();
    void composeScene();

    std::shared_ptr<MenuView> _menuView;
    std::shared_ptr<GameMenu> _gameMenu;

    std::shared_ptr<Scene::Scene> _scene;
    std::shared_ptr<Scene::Player> _player;
    std::shared_ptr<GameView> _gameView;

    MouseMoveEvent _latestMouseMoveEvent;
};
