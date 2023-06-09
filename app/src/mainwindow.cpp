#include "mainwindow.h"

#include "scene/items/player/player.h"
#include "scene/items/testitem.h"
#include "scene/scene.h"
#include "scene/textures/textures.h"

#include "event/keyevents/keypressevent.h"
#include "event/keyevents/keyreleaseevent.h"
#include "event/mouseevents/mousepressevent.h"
#include "event/mouseevents/mousereleaseevent.h"

#include "geometry/rect.h"
#include "geometry/utils.h"

#include "view/gameview.h"
#include "view/menuview.h"

#include "menu/gamemenu.h"

#include <SFML/Graphics/Drawable.hpp>

std::shared_ptr<sf::Texture> playerTexture{ std::make_shared<sf::Texture>() };

MainWindow::MainWindow(unsigned int width, unsigned int height, const char *name)
    : sf::RenderWindow{ sf::VideoMode({ width, height }), name },
      _menuView{ std::make_shared<MenuView>(
          RectF{ { 0.f, 0.f }, { static_cast<float>(width), static_cast<float>(height) } }, this) },
      _gameMenu{ std::make_shared<GameMenu>(this) },
      _scene{ std::make_shared<Scene::Scene>(this) },
      _player{ std::make_shared<Scene::Player>(
          std::make_shared<sf::Texture>(Scene::playerTexture()), _scene.get()) },
      _gameView{ std::make_shared<GameView>(
          RectF{ _player->center(), { static_cast<float>(width), static_cast<float>(height) } },
          this) },
      _latestMouseMoveEvent{ {}, {} }
{
    composeMenu();
    composeScene();
}

MainWindow::~MainWindow()
{
}

int MainWindow::gameLoop()
{
    while (isOpen())
    {
        sf::Event event;
        while (pollEvent(event))
        {
            handleSfmlEvent(event);
        }

        setView(*_menuView);

        _gameMenu->render(*this, sf::RenderStates::Default);
        display();
    }

    return 0;
}

void MainWindow::handleSfmlEvent(const sf::Event &event)
{
    switch (event.type)
    {
    case sf::Event::Closed:
    {
        close();
        break;
    }
    case sf::Event::KeyPressed:
    {
        KeyPressEvent e{ Keyboard::Key(event.key.code), event.key.shift, event.key.alt,
                         event.key.control };
        handleEvent(&e);
        break;
    }
    case sf::Event::KeyReleased:
    {
        KeyReleaseEvent e{ Keyboard::Key(event.key.code), event.key.shift, event.key.alt,
                           event.key.control };
        handleEvent(&e);
        break;
    }
    case sf::Event::MouseButtonPressed:
    {
        sf::Vector2f sfmlPos{ mapPixelToCoords(sf::Mouse::getPosition(*this), this->getView()) };
        MousePressEvent e{ Mouse::Button(event.mouseButton.button), Geometry::toPoint(sfmlPos) };

        handleEvent(&e);
        break;
    }
    case sf::Event::MouseButtonReleased:
    {
        sf::Vector2f sfmlPos{ mapPixelToCoords(sf::Mouse::getPosition(*this), this->getView()) };
        MouseReleaseEvent e{ Mouse::Button(event.mouseButton.button), Geometry::toPoint(sfmlPos) };

        handleEvent(&e);
        break;
    }
    case sf::Event::MouseMoved:
    {
        MouseMoveEvent e{ { static_cast<float>(event.mouseMove.x),
                            static_cast<float>(event.mouseMove.y) },
                          _latestMouseMoveEvent.position() };
        handleEvent(&e);
        _latestMouseMoveEvent = e;
        break;
    }
    default:
        break;
    }
}

void MainWindow::composeMenu()
{
}

void MainWindow::composeScene()
{
    std::shared_ptr<Scene::TestItem> item1{ std::make_shared<Scene::TestItem>() };
    std::shared_ptr<Scene::TestItem> item2{ std::make_shared<Scene::TestItem>() };
    std::shared_ptr<Scene::TestItem> item3{ std::make_shared<Scene::TestItem>() };
    std::shared_ptr<Scene::TestItem> item4{ std::make_shared<Scene::TestItem>() };

    item1->setPos({ -20, 300 });
    item2->setPos({ 35, -70 });
    item3->setPos({ 400, 320 });
    item4->setPos({ 400, 400 });

    _scene->addItem(item1);
    _scene->addItem(item2);
    _scene->addItem(item3);
    _scene->addItem(item4);

    _scene->addItem(_player);
    _scene->addToCollisionDetection(_player);
}
