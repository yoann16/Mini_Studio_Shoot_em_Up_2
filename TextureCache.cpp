#include "TextureCache.h"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

TextureCache::TextureCache(const std::string& execFilePath) : m_execFilePath(execFilePath)
{}

TextureCache::~TextureCache()
{
    for (auto& textureInfo : m_allTextureInfos)
        delete textureInfo.texture;
    m_allTextureInfos.clear();
}

std::string TextureCache::getAbsoluteFilepath(const std::string& filename)
{
    std::filesystem::path execFilePath(m_execFilePath);

    
    auto projectRootPath = execFilePath.parent_path().parent_path().parent_path().parent_path();

    auto resourcePath = projectRootPath / "Ressources" / std::filesystem::path(filename);

    if (!std::filesystem::exists(resourcePath)) {
        std::cerr << "Fichier non trouvé : " << resourcePath << std::endl;
    }

    return resourcePath.string();
}

sf::Texture& TextureCache::getTexture(const std::string& filename)
{
    std::string path = getAbsoluteFilepath(filename);
    for (auto& texture : m_allTextureInfos)
    {
        if (texture.path == path)
            return *texture.texture;
    }

    TextureInfo ti;
    ti.path = path;
    ti.texture = new sf::Texture;
    ti.texture->loadFromFile(path);
    m_allTextureInfos.pushBack(ti);

    return *ti.texture;
}
