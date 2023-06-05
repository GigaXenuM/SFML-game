#include "textures.h"

#include <iostream>
namespace Scene
{
sf::Texture playerTexture()
{
    sf::Texture texture;
    bool loaded{ texture.loadFromFile("res/assets/player/player.png") };

    if (!loaded)
        std::cerr << "Failed to load Player`s texture." << std::endl;

    return texture;
}
} // namespace Scene
