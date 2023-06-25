#include "textbutton.h"

#include "event/mouseevents/mousepressevent.h"
#include "event/mouseevents/mousereleaseevent.h"

#include "geometry/alignment.h"
#include "geometry/utils.h"

#include "SFML/Graphics/RenderTarget.hpp"

namespace Scene
{
TextButton::TextButton(const std::string &text, const sf::Font &font, SizeF size,
                       EventHandler *parent)
    : Item{ parent },
      _text{ text },
      _font{ font },
      _textItem{ _font, _text },
      _shape{ Geometry::toSfmlSize(size) },
      _onClickCallback{ []() {} }
{
    if (parent != nullptr)
        parent->addEventHandler(this);

    setup();
    updateGeometry();
}

void TextButton::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
{
    target.draw(_shape, states);
    target.draw(_textItem, states);
}

void TextButton::setPos(PointF position)
{
    _shape.setPosition(Geometry::toSfmlPoint(position));
    updateGeometry();
}

void TextButton::setOrigin(Align origin)
{
    _shape.setOrigin(Geometry::toSfmlPoint(localRect().pointBy(origin)));
}

RectF TextButton::globalRect() const
{
    return Geometry::toRect(_shape.getGlobalBounds());
}

RectF TextButton::localRect() const
{
    return Geometry::toRect(_shape.getLocalBounds());
}

PointF TextButton::center() const
{
    sf::FloatRect bound{ _shape.getGlobalBounds() };
    return { bound.left + bound.width / 2.f, bound.top + bound.height / 2.f };
}

void TextButton::setTextColor(sf::Color color)
{
    _textItem.setFillColor(color);
}

void TextButton::setBackgroundColor(sf::Color color)
{
    _shape.setFillColor(color);
}

void TextButton::onClick(OnClickCallback callback)
{
    _onClickCallback = callback;
}

void TextButton::mousePressEvent(MousePressEvent *event)
{
    if (event->button() != Mouse::Button::Left)
        return;

    RectF rect{ globalRect() };
    bool mouseHovered{ event->position().x > rect.pos.x
                       && event->position().x < rect.pos.x + rect.width()
                       && event->position().y > rect.pos.y
                       && event->position().y < rect.pos.y + rect.height() };

    if (mouseHovered)
    {
        _shape.setFillColor(sf::Color::Red);
        _pressed = true;
    }
}

void TextButton::mouseReleaseEvent(MouseReleaseEvent *event)
{
    if (event->button() != Mouse::Button::Left)
        return;

    if (_pressed)
    {
        _shape.setFillColor({ 50, 50, 50 });
        _onClickCallback();
        _pressed = false;
    }
}

void TextButton::setup()
{
    _shape.setFillColor({ 50, 50, 50 });

    sf::FloatRect textBound{ _textItem.getLocalBounds() };
    sf::FloatRect shapeBound{ _shape.getLocalBounds() };

    if (textBound.width > shapeBound.width)
        _shape.setSize({ textBound.width, shapeBound.height });
    if (textBound.height > shapeBound.height)
        _shape.setSize({ shapeBound.width, textBound.height });

    sf::Vector2f textCenter{ textBound.left + textBound.width / 2.f,
                             textBound.top + textBound.height / 2.f };
    _textItem.setOrigin(textCenter);
}

void TextButton::updateGeometry()
{
    _textItem.setPosition(Geometry::toSfmlPoint(center()));
}
} // namespace Scene
