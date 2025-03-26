#include "Map.h"
#include <iostream>
#include <filesystem>

Map::Map() : m_imagePaths({
    "..\\..\\Ressources\\map haut gauche.png",
    "..\\..\\Ressources\\map haut droite.png",
    "..\\..\\Ressources\\map bas gauche.png",
    "..\\..\\Ressources\\map bas droite.png"
    }) {
}

sf::Image Map::resizeImage(const sf::Image& image, sf::Vector2u newSize) {
    sf::Image resizedImage;
    resizedImage.create(newSize.x, newSize.y);

    float scaleX = static_cast<float>(image.getSize().x) / newSize.x;
    float scaleY = static_cast<float>(image.getSize().y) / newSize.y;

    for (unsigned int y = 0; y < newSize.y; ++y) {
        for (unsigned int x = 0; x < newSize.x; ++x) {
            unsigned int srcX = static_cast<unsigned int>(x * scaleX);
            unsigned int srcY = static_cast<unsigned int>(y * scaleY);

            resizedImage.setPixel(x, y, image.getPixel(srcX, srcY));
        }
    }

    return resizedImage;
}

bool Map::assemblePngImages(const std::string& outputPath) {
    sf::Vector2u outputSize(4000, 4000);

    if (m_imagePaths.size() != 4) {
        std::cerr << "Error : Exactly 4 images are required." << std::endl;
        return false;
    }

    sf::Image assembledImage;
    assembledImage.create(outputSize.x, outputSize.y, sf::Color::Transparent);

    try {
        sf::Vector2u quadrantSize(outputSize.x / 2, outputSize.y / 2);

        std::vector<sf::Vector2u> quadrantPositions = {
            sf::Vector2u(0, 0),           // Haut gauche
            sf::Vector2u(quadrantSize.x, 0),  // Haut droite
            sf::Vector2u(0, quadrantSize.y), // Bas gauche
            sf::Vector2u(quadrantSize.x, quadrantSize.y) // Bas droite
        };

        for (size_t i = 0; i < 4; ++i) {
            sf::Image image;
            if (!image.loadFromFile(m_imagePaths[i])) {
                std::cerr << "Error : Impossible to load the image " << m_imagePaths[i] << std::endl;
                return false;
            }

            sf::Image processedImage = (image.getSize() != quadrantSize)
                ? resizeImage(image, quadrantSize)
                : image;

            for (unsigned int y = 0; y < quadrantSize.y; ++y) {
                for (unsigned int x = 0; x < quadrantSize.x; ++x) {
                    sf::Color pixel = processedImage.getPixel(x, y);
                    assembledImage.setPixel(
                        quadrantPositions[i].x + x,
                        quadrantPositions[i].y + y,
                        pixel
                    );
                }
            }
        }

        std::string relativeOutputPath = "..\\..\\Ressources\\" + outputPath;
        return assembledImage.saveToFile(relativeOutputPath);
    }
    catch (const std::exception& e) {
        std::cerr << "Error : " << e.what() << std::endl;
        return false;
    }
}