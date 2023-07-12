#include "mainwindow.h"

#include "layout/verticallayout.h"

#include "scene/items/button/textbutton.h"
#include "scene/items/player/player.h"
#include "scene/items/rectangles/collisionrect.h"
#include "scene/items/rectangles/rect.h"
#include "scene/scene.h"
#include "scene/textures/textures.h"

#include "event/keyevents/keypressevent.h"
#include "event/keyevents/keyreleaseevent.h"
#include "event/mouseevents/mousepressevent.h"
#include "event/mouseevents/mousereleaseevent.h"

#include "geometry/rect.h"
#include "geometry/utils.h"

#include "view/iview.h"
#include "view/menuview.h"
#include "view/sceneview.h"

#include "menu/menu.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <iostream>

std::shared_ptr<sf::Texture> playerTexture{ std::make_shared<sf::Texture>() };

MainWindow::MainWindow(unsigned int width, unsigned int height, const char *name)
    : sf::RenderWindow{ sf::VideoMode({ width, height }), name },
      _menuView{ std::make_shared<MenuView>(
          this, RectF{ { 0.f, 0.f }, { static_cast<float>(width), static_cast<float>(height) } },
          this) },
      _menu{ std::make_shared<Menu>(this, this) },
      _scene{ std::make_shared<Scene::Scene>(this, this) },
      _player{ new Scene::Player(std::make_shared<sf::Texture>(Scene::playerTexture()),
                                 _scene.get()) },
      _sceneView{ std::make_shared<SceneView>(
          this,
          RectF{ _player->center(), { static_cast<float>(width), static_cast<float>(height) } },
          this) },
      _latestMouseMoveEvent{ {}, {} },
      _renderer{ _menu },
      _view{ _menuView }
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
        float deltatime{ _clock.restart().asSeconds() };

        sf::Event event;
        while (pollEvent(event))
            handleSfmlEvent(event);

        _view->update(deltatime);
        _renderer->render(deltatime);

        display();
    }

    return 0;
}

void MainWindow::keyPressEvent(KeyPressEvent *event)
{
    if (event->key() == Keyboard::Key::Escape)
        switchContent();
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
    case sf::Event::Resized:
    {
        _menuView->setSize(
            { static_cast<float>(event.size.width), static_cast<float>(event.size.height) });
        _sceneView->setSize(
            { static_cast<float>(event.size.width), static_cast<float>(event.size.height) });
        break;
    }
    default:
        break;
    }
}

void MainWindow::composeMenu()
{
    auto layout{ std::make_shared<VerticalLayout>(
        static_cast<RectF>(Geometry::toRect(getViewport(getView()))), this) };
    layout->setSpacing(20);

    _menu->setLayout(std::move(layout));
    sf::Font font;
    bool successLoad{ font.loadFromFile("res/fonts/arial.ttf") };
    if (!successLoad)
        std::cerr << "GameMenu: Failed load font." << std::endl;

    auto startButton{ std::make_shared<Scene::TextButton>("Start Game", font,
                                                          SizeF{ 180.0f, 50.0f }, this) };
    auto exitButton{ std::make_shared<Scene::TextButton>("Exit", font, SizeF{ 180.0f, 50.0f },
                                                         this) };

    startButton->onClick([this]() { switchContent(); });
    exitButton->onClick([this]() { close(); });

    _menu->addItem(startButton);
    _menu->addItem(exitButton);
}

void MainWindow::composeScene()
{
    Scene::Item *item1{ new Scene::CollisionRect() };
    Scene::Item *item2{ new Scene::CollisionRect() };
    Scene::Item *item3{ new Scene::CollisionRect() };
    Scene::Item *item4{ new Scene::Rect() };

    item1->setPos({ -100, 250 });
    item2->setPos({ 123, -70 });
    item3->setPos({ 250, -175 });
    item4->setPos({ -200, 50 });

    _scene->addItem(item1);
    _scene->addItem(item2);
    _scene->addItem(item3);
    _scene->addItem(item4);

    _scene->addItem(_player);

    _sceneView->setCenterTarget(_player);
}

void MainWindow::switchContent()
{
    _showMenu = !_showMenu;

    if (_showMenu)
        switchToMenu();
    else
        switchToGame();
}

void MainWindow::switchToGame()
{
    _renderer = _scene;
    _view = _sceneView;
}

void MainWindow::switchToMenu()
{
    _renderer = _menu;
    _view = _menuView;
}
