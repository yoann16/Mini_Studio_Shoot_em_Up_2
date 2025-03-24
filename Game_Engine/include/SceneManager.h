#pragma once
#include<string>
#include <SFML/Graphics.hpp>
#include "Composite.h"
#include "SceneBase.h"
#include "TextureCache.h"
//#include "KT_Vector.h"

class ISceneBase;
using sfStyle = int;

class SceneManager : public IComposite
{
public:

	SceneManager(Root* root, const std::string& execFilePath, const size_t& width, const size_t& height,
				const std::string& title, const sfStyle& style = sf::Style::Default);

	~SceneManager();
	void Exe();

	void AddScene( ISceneBase* scene);

	void SetScene(const int& idx);

	sf::RenderWindow* getWindow();

	TextureCache* getTextureCash();
private:
	sf::RenderWindow* m_window;
	std::vector<ISceneBase*> m_scene;
	ISceneBase* m_currentScene;
	sf::Event m_event;
	TextureCache* m_texture;
};
