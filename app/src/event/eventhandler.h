#pragma once

#include <vector>

class Event;
class KeyPressEvent;
class KeyReleaseEvent;

class EventHandler
{
public:
    virtual ~EventHandler() = default;

    virtual void handleEvent(Event *event);

    std::vector<EventHandler *> eventHandlers() const;

    void addEventHandler(EventHandler *handler);
    void removeEventHandler(EventHandler *handler);

    virtual void keyPressEvent(KeyPressEvent *event);
    virtual void keyReleaseEvent(KeyReleaseEvent *event);

private:
    std::vector<EventHandler *> _handlers;
};
