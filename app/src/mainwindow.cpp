#include "mainwindow.h"

#include "scene/items/player/player.h"
#include "scene/items/testitem.h"
#include "scene/scene.h"

#include "event/keyevents/keypressevent.h"
#include "event/keyevents/keyreleaseevent.h"
#include "event/mouseevents/mousepressevent.h"
#include "event/mouseevents/mousereleaseevent.h"

#include "geometry/rect.h"
#include "view/view.h"

#include <SFML/Graphics/Drawable.hpp>

MainWindow::MainWindow(unsigned int width, unsigned int height, const char *name)
    : sf::RenderWindow{ sf::VideoMode({ width, height }), name },
      _scene{ new Scene::Scene(this) },
      _player{ new Scene::Player{ _scene } },
      _view{ new View{
          RectF{ _player->center(), { static_cast<float>(width), static_cast<float>(height) } },
          this } },
      _lastMouseMoveEvent{ { static_cast<float>(sf::Mouse::getPosition().x),
                             static_cast<float>(sf::Mouse::getPosition().y) },
                           {} }
{
    _scene->addItem(_player);
    _scene->addToCollisionDetection(_player);

    Scene::TestItem *item1{ new Scene::TestItem };
    Scene::TestItem *item2{ new Scene::TestItem };
    Scene::TestItem *item3{ new Scene::TestItem };

    item1->setPos({ -20, 300 });
    item2->setPos({ 35, -70 });
    item3->setPos({ 400, 320 });

    _scene->addItem(item1);
    _scene->addItem(item2);
    _scene->addItem(item3);
}

MainWindow::~MainWindow()
{
    delete _scene;
    delete _player;
    delete _view;
}

int MainWindow::runLoop()
{
    while (isOpen())
    {
        sf::Event event;
        while (pollEvent(event))
        {
            handleSfmlEvent(event);
        }

        setView(*_view);

        clear(sf::Color(134, 145, 144, 255));
        _scene->render(this, &sf::RenderStates::Default);
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
        KeyPressEvent e{ Keyboard::Key(event.key.code) };
        handleEvent(&e);
        break;
    }
    case sf::Event::KeyReleased:
    {
        KeyReleaseEvent e{ Keyboard::Key(event.key.code) };
        handleEvent(&e);
        break;
    }
    case sf::Event::MouseButtonPressed:
    {
        MousePressEvent e{ Mouse::Button(event.mouseButton.button) };
        handleEvent(&e);
        break;
    }
    case sf::Event::MouseButtonReleased:
    {
        MouseReleaseEvent e{ Mouse::Button(event.mouseButton.button) };
        handleEvent(&e);
        break;
    }
    case sf::Event::MouseMoved:
    {
        MouseMoveEvent e{ { static_cast<float>(event.mouseMove.x),
                            static_cast<float>(event.mouseMove.y) },
                          _lastMouseMoveEvent.pos() };
        handleEvent(&e);
        _lastMouseMoveEvent = e;
        break;
    }
    default:
        break;
    }
}
