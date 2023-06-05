#pragma once

#include "geometry/point.h"
#include "geometry/rect.h"

#include <SFML/Graphics/Texture.hpp>

namespace Scene
{

class Animation
{
    using TexturePosition = Point<size_t>;
    using ViewRect = Rect<size_t>;

public:
    explicit Animation(std::shared_ptr<sf::Texture> texture, size_t columnCount, size_t rowCount,
                       float switchTime);

    void setColumn(size_t column);
    void setRow(size_t row);
    void setTexture(std::shared_ptr<sf::Texture> texture, size_t columnCount, size_t rowCount);
    void setSwitchTime(float switchTime);

    void update(float deltaTime);

    ViewRect viewRect() const;

private:
    void updateViewRect();
    void switchFrame();

    std::shared_ptr<sf::Texture> _texture;
    size_t _columnCount;
    size_t _rowCount;
    float _switchTime;

    ViewRect _viewRect;
    TexturePosition _texturePos;
    float _totalTime{ 0.0f };
};
} // namespace Scene
