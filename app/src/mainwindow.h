#pragma once

#include "event/eventhandler.h"
#include "event/mouseevents/mousemoveevent.h"

#include <SFML/Graphics/RenderWindow.hpp>

class Menu;
class MenuView;
class SceneView;
class IRenderer;
class IView;

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

protected:
    void keyPressEvent(KeyPressEvent *event) override;

private:
    void handleSfmlEvent(const sf::Event &event);

    void composeMenu();
    void composeScene();

    void switchContent();
    void switchToGame();
    void switchToMenu();

    sf::Clock _clock;

    std::shared_ptr<MenuView> _menuView;
    std::shared_ptr<Menu> _menu;

    std::shared_ptr<Scene::Scene> _scene;
    Scene::Player *_player;
    std::shared_ptr<SceneView> _sceneView;

    MouseMoveEvent _latestMouseMoveEvent;

    std::shared_ptr<IRenderer> _renderer;
    std::shared_ptr<IView> _view;

    bool _showMenu{ true };
};
