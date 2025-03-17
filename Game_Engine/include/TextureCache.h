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


