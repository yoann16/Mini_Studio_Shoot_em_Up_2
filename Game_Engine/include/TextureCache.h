#pragma once
#include "KT_Vector.h"
#include <string>

namespace sf { class Texture; }

class TextureCache
{
public:

	TextureCache(const std::string& execFilePath);

	sf::Texture& getTexture(const std::string& filename);

	~TextureCache();

private:
	struct TextureInfo
	{
		sf::Texture* texture;
		std::string path;
	};

	std::string getAbsoluteFilepath(const std::string& filename);

	KT::Vector<TextureInfo> m_allTextureInfos;
	std::string m_execFilePath;
};

class AnimateSprite
{
public:
	AnimateSprite(std::initializer_list<std::string> init);

	void add(std::string toBeAdded);

	std::string getPath(const std::string& check);

	std::string getPath(const int& idx);

	std::string getCurrentPath();

	void resetTexture();

	void ChangeToNextPath();

	void ChangeToPreviousPath();

	void ChangePath(const int& idx);


private:
	KT::Vector<std::string> m_textureContainer;
	int m_curentTexture;
};


