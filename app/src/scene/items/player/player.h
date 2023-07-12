#pragma once

#include "scene/animation/animation.h"
#include "scene/items/collisionhandler.h"

#include "event/keyevents/keyboard.h"
#include "geometry/point.h"

#include "SFML/Graphics/Texture.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <array>
#include <memory>

class EventHandler;

namespace Scene
{

class Player : public CollisionHandler
{
public:
    explicit Player(std::shared_ptr<sf::Texture> texture, EventHandler *parent);
    virtual ~Player() = default;

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    RectF globalRect() const override;
    RectF localRect() const override;
    RectF collisionRect() const override;
    PointF center() const override;
    Vertices vertices() const override;

    void update(float deltatime) override;
    void setPos(PointF position) override;
    void setOrigin(Align origin) override;

    void handleCollision(const CollisionItem *item) override;

protected:
    void keyPressEvent(KeyPressEvent *event) override;
    void keyReleaseEvent(KeyReleaseEvent *event) override;

private:
    void handleMoving(float deltaTime);

    std::shared_ptr<sf::Texture> _texture;
    sf::Sprite _drawableItem;

    Animation _animation;
    std::array<bool, static_cast<size_t>(Keyboard::Key::MAX_SIZE)> _keyStates;
    Keyboard::Mode _keyboardMode;
};
} // namespace Scene
