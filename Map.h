#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Map {
public:
    Map();

    bool assemblePngImages(const std::string& outputPath);

private:
    sf::Image resizeImage(const sf::Image& image, sf::Vector2u newSize);

    std::vector<std::string> m_imagePaths;
};

#endif // MAP_H