//#include "Game.h"
//#include "Ship.h"
//#include "IGameObject.h"
//#include <iostream>
//
//Game::Game(sf::RenderWindow* window, const float& framerate, TextureCache* texture) :
//	ISceneBase(window, framerate, texture),
//	cursor(this),
//	m_bossSpawnTimer(10.0f)
//{
//	m_Background = new SquareSFML(10000, sf::Vector2f(0, 0));
//	m_Background->setTexture(m_texture->getTexture("galaxie4.png"));
//	m_ship = new Ship(this, m_Background);
//	new BorderShip(m_ship, m_Background, static_cast<Ship*>(m_ship));
//	new GameBorder(this, m_Background, Position::Down, 5);
//	new GameBorder(this, m_Background, Position::Up, 5);
//	new GameBorder(this, m_Background, Position::Left, 5);
//	new GameBorder(this, m_Background, Position::Right, 5);
//	new WorldBorder(this, m_Background, Position::Down, 5, 1000);
//	new WorldBorder(this, m_Background, Position::Up, 5, 1000);
//	new WorldBorder(this, m_Background, Position::Left, 5, 1000);
//	new WorldBorder(this, m_Background, Position::Right, 5, 1000);
//	m_spawner = new AsteroidSpawner(this, 10);
//	m_bossSpawner = new BossSpawner(this, 1);
//	sf::Vector2f bossSpawnPosition(GetCenterWindow().x, GetCenterWindow().y - 300);
//	m_bossSpawner->SetSpawnPosition(bossSpawnPosition);
//
//	getWindow()->setMouseCursorVisible(false);
//}
//
//void Game::Update(const float& deltatime)
//{
//	for (auto& obj : getChildren())
//	{
//		obj->Update(deltatime);
//	}
//	cursor.Update(deltatime);
//	m_spawner->Spawn();
//
//	m_bossSpawnTimer.NextTIck(deltatime);
//	if (m_bossSpawnTimer.ActionIsReady()) {
//		m_bossSpawner->Spawn();
//		m_bossSpawnTimer.setNewTimer(9999999999999999.0f);
//	}
//
//	auto vec = getFullTree();
//	collision.HandleCollision(vec);
//}
//
//void Game::ProssesInput(const sf::Event& event)
//{
//	for (auto& obj : getChildren())
//	{
//		obj->ProssesInput(event);
//	}
//	cursor.ProssesInput(event);
//}
//
//void Game::Render()
//{
//	getWindow()->draw(static_cast<SquareSFML*>(m_Background)->getShape());
//	for (auto& obj : getChildren())
//	{
//		obj->Render();
//	}
//	cursor.Render();
//}