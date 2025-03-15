#include "SceneManager.h"
#include "SceneBase.h"
#include <iostream>

SceneManager::SceneManager(const std::string& execFilePath,const size_t& width, const size_t& height, const std::string& title, const sfStyle& style) :
m_window(new sf::RenderWindow(sf::VideoMode(width, height)
	, title, style))
, m_currentScene(nullptr)
,m_texture(new TextureCache(execFilePath))
{}

SceneManager::~SceneManager()
{
	delete m_window;
	m_window = nullptr;

	for (std::make_signed_t<size_t> idx = m_scene.Size() - 1 ; idx >= 0; --idx)
	{
		delete m_scene[idx];
		m_scene[idx] = nullptr;
	}
	m_scene.clear();

	delete m_texture;
	m_texture = nullptr;
}

void SceneManager::Exe()
{
	const sf::Clock clock;
	const sf::Clock spawnClock;
	float previous = clock.getElapsedTime().asMilliseconds();
	auto lag = 0.0;
	int frameCount = 0;
	while (m_window->isOpen())
	{
		frameCount++;
		const float current = clock.getElapsedTime().asMilliseconds();
		const float maxElapsed = 250.0f;
		const auto elapsed = current - previous;
		float cappedElapsed = (elapsed > maxElapsed) ? maxElapsed : elapsed;
		previous = current;
		lag += cappedElapsed;
		/*std::cout << "Frame " << frameCount << ": elapsed=" << elapsed
			<< "ms, lag=" << lag << "ms" << std::endl;*/

		SetScene(m_currentScene->getSceneIdx());

		m_window->clear();

		while (m_window->pollEvent(m_event)) 
		{
			if (m_event.type == sf::Event::Closed ||
				(m_event.type == sf::Event::KeyPressed && m_event.key.code == sf::Keyboard::Escape)) {
				m_window->close();
			}
			m_currentScene->ProcessInput(m_event);
		}

		if (m_window->hasFocus())
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
			if (mousePos.x >= 0 && mousePos.x < m_window->getSize().x && mousePos.y >= 0 && mousePos.y < m_window->getSize().y)
			{
				//m_currentScene->ProcessInput(m_event);
			}
		}

		const float fixedTimeStep = 1.0f / 60.0f;
		const float fixedTimeStepMs = fixedTimeStep * 1000.0f;
		int updateCount = 0;
		const int maxUpdatesPerFrame = 5;
		while (lag >= fixedTimeStepMs && updateCount < maxUpdatesPerFrame)
		{
			m_currentScene->Update(fixedTimeStep);
			lag -= fixedTimeStepMs;
			updateCount++;
		}
		m_currentScene->Render();
		m_window->display();
	}
}

void SceneManager::AddScene(ISceneBase* scene)
{
	m_scene.pushBack(scene);
	m_scene.back()->setSceneIdx(m_scene.Size() - 1);
	if (m_scene.Size() == 1)
	{
		SetScene(0);
	}
}

void SceneManager::SetScene(const int& idx)
{ 

	m_currentScene = m_scene[idx];
}

sf::RenderWindow* SceneManager::getWindow() 
{
	return m_window; 
}

TextureCache* SceneManager::geTextureCash()
{
	return m_texture;
}
