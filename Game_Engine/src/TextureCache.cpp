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

AnimateSprite::AnimateSprite(std::initializer_list<std::string> init) : m_curentTexture(0)
{
	for (auto& idx : init)
	{
		m_textureContainer.pushBack(idx);
	}
}

void AnimateSprite::add(std::string toBeAdded)
{
	m_textureContainer.pushBack(toBeAdded);
}

std::string AnimateSprite::getPath(const std::string& check)
{
	if (m_textureContainer.Empty())
		throw std::out_of_range("Vector is empty");
	for (auto& idx : m_textureContainer)
	{
		if (idx == check)
			return idx;
	}
	throw std::runtime_error("Impossible to find path");
}

std::string AnimateSprite::getPath(const int& idx)
{
	if (m_textureContainer.Empty())
		throw std::out_of_range("Vector is empty");
	if (idx >= m_textureContainer.Size())
		throw std::out_of_range("Out of range");
	return m_textureContainer[idx];
}

std::string AnimateSprite::getCurrentPath()
{
	return m_textureContainer[m_curentTexture];
}

void AnimateSprite::resetTexture()
{
	m_textureContainer.clear();
	m_curentTexture = 0;
}

void AnimateSprite::ChangeToNextPath()
{
	if (m_textureContainer.Empty())
		throw std::out_of_range("Vector is empty");
	if (m_curentTexture == m_textureContainer.Size() - 1)
		m_curentTexture = 0;
	else
		++m_curentTexture;
}

void AnimateSprite::ChangePath(const int& idx)
{
	if (idx < 0 || idx >= m_textureContainer.Size())
		throw std::runtime_error("Out of range");
	m_curentTexture = idx;
}

void AnimateSprite::ChangeToPreviousPath()
{
	if (m_textureContainer.Empty())
		throw std::out_of_range("Vector is empty");
	if (m_curentTexture == 0)
		m_curentTexture = m_textureContainer.Size() - 1;
	else
		--m_curentTexture;
}
