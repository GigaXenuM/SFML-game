#include "animation.h"

namespace Scene
{

Animation::Animation(std::shared_ptr<sf::Texture> texture, size_t columnCount, size_t rowCount,
                     float switchTime)
    : _texture{ std::move(texture) },
      _columnCount{ columnCount },
      _rowCount{ rowCount },
      _switchTime{ switchTime },
      _viewRect{ { 0, 0 },
                 { _texture->getSize().x / _columnCount, _texture->getSize().y / _rowCount } },
      _texturePos{ 0, 0 }
{
}

void Animation::setColumn(size_t column)
{
    if (column >= _columnCount)
    {
        _texturePos.setX(_columnCount - 1);
        return;
    }

    _texturePos.setX(column);
    updateViewRect();
}

void Animation::setRow(size_t row)
{
    if (row >= _rowCount)
    {
        _texturePos.setY(_rowCount - 1);
        return;
    }

    _texturePos.setY(row);
    updateViewRect();
}

void Animation::setTexture(std::shared_ptr<sf::Texture> texture, size_t columnCount,
                           size_t rowCount)
{
    _texture = std::move(texture);
    _columnCount = columnCount;
    _rowCount = rowCount;
    _viewRect
        = ViewRect{ { 0, 0 },
                    { _texture->getSize().x / _columnCount, _texture->getSize().y / _rowCount } };
}

void Animation::setSwitchTime(float switchTime)
{
    _switchTime = switchTime;
}

void Animation::update(float deltaTime)
{
    _totalTime += deltaTime;
    if (_totalTime >= _switchTime)
    {
        _totalTime -= _switchTime;
        switchFrame();
    }
}

Animation::ViewRect Animation::viewRect() const
{
    return _viewRect;
}

void Animation::updateViewRect()
{
    _viewRect.pos = { _texturePos.x() * _viewRect.width(), _texturePos.y() * _viewRect.height() };
}

void Animation::switchFrame()
{
    _texturePos.moveX(1);
    if (_texturePos.x() >= _columnCount)
        _texturePos.setX(0);

    updateViewRect();
}

} // namespace Scene
