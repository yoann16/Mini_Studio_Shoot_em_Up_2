#pragma once
#include<string>
#include <SFML/Graphics.hpp>
#include "KT_Vector.h"
#include "TextureCache.h"

class ISceneBase;
using sfStyle = int;

class SceneManager
{
public:

	SceneManager(const std::string& execFilePath, const size_t& width, const size_t& height, const std::string& title, const sfStyle& style = sf::Style::Default);

	~SceneManager();
	void Exe();

	void AddScene( ISceneBase* scene);

	void SetScene(const int& idx);

	sf::RenderWindow* getWindow();

	TextureCache* geTextureCash();
private:
	sf::RenderWindow* m_window;
	KT::Vector<ISceneBase*> m_scene;
	ISceneBase* m_currentScene;
	sf::Event m_event;
	TextureCache* m_texture;
};
