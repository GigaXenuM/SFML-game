#include "eventhandler.h"

#include "event.h"
#include "event/keyevents/keypressevent.h"
#include "event/keyevents/keyreleaseevent.h"

void EventHandler::handleEvent(Event *event)
{
    switch (event->type())
    {
    case Event::EventType::KEY_PRESS:
        keyPressEvent(dynamic_cast<KeyPressEvent *>(event));
        break;
    case Event::EventType::KEY_RELEASE:
        keyReleaseEvent(dynamic_cast<KeyReleaseEvent *>(event));
        break;
    case Event::EventType::MOUSE_MOVE:
    case Event::EventType::MOUSE_PRESS:
    case Event::EventType::MOUSE_RELEASE:
    case Event::EventType::MOUSE_SCROLL:
        break;
    }

    for (auto *handler : eventHandlers())
        handler->handleEvent(event);
}

std::vector<EventHandler *> EventHandler::eventHandlers() const
{
    return _handlers;
}

void EventHandler::addEventHandler(EventHandler *handler)
{
    _handlers.push_back(handler);
}

void EventHandler::removeEventHandler(EventHandler *handler)
{
    auto toRemove{ std::find(_handlers.begin(), _handlers.end(), handler) };
    _handlers.erase(toRemove);
}

void EventHandler::keyPressEvent(KeyPressEvent * /*event*/)
{
    // Override it to define the logic.
}

void EventHandler::keyReleaseEvent(KeyReleaseEvent * /*event*/)
{
    // Override it to define the logic.
}
