#include "mainwindow.h"

#include "scene/items/player/player.h"
#include "scene/scene.h"

#include "event/keyevents/keypressevent.h"
#include "event/keyevents/keyreleaseevent.h"

MainWindow::MainWindow(unsigned int width, unsigned int height, const char *name)
    : sf::RenderWindow{ sf::VideoMode({ width, height }), name },
      _scene{ new Scene::Scene(this) },
      _player{ new Scene::Player{ _scene } }
{
    _scene->addItem(_player);
}

MainWindow::~MainWindow()
{
    delete _scene;
}

int MainWindow::runLoop()
{
    while (isOpen())
    {
        sf::Event event;
        while (pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                close();
            }
            case sf::Event::KeyPressed:
            {
                KeyPressEvent e{ Keyboard::Key(event.key.code) };
                handleEvent(&e);
            }
            case sf::Event::KeyReleased:
            {
                KeyReleaseEvent e{ Keyboard::Key(event.key.code) };
                handleEvent(&e);
            }
            default:
                break;
            }
        }

        clear();
        _scene->draw(this, &sf::RenderStates::Default);
        display();
    }

    return 0;
}
