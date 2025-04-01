#pragma once
#include<string>
#include <SFML/Graphics.hpp>
#include "Composite.h"
#include "SceneBase.h"
#include "TextureCache.h"
/*TODO CREER UNE CLASSE WINDOW
Severity	Code	Description	Project	File	Line	Suppression State	Details
Warning	C26495	Variable 'SceneManager::m_event' is uninitialized.
Always initialize a member variable(type.6).Game_Engine
E : \Projet_et_Etude\GamingCampus\ent\Mini_Studio_Shoot_Em_Up\Mini_Studio_Shoot_em_Up_2\Game_Engine\src\SceneManager.cpp 4*/

class ISceneBase;
using sfStyle = int;

class SceneManager : public IComposite
{
public:

	SceneManager(Root* root, const std::string& execFilePath, const unsigned int& width, const unsigned int& height,
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
