#pragma once
#include "IGameObject.h"
#include "IShape.h"
#include "Layer.h"
#include "KT_Math_Algorithm.h"
#include "KT_Array.h"
#include "KT_VectorND.h"
#include "Game.h"
#include <iostream>
#include <random>

class Terrain : public NonDestructibleObject, public IComposite
{
public:
	Terrain(Layer* scene, const sf::Vector2f& position)
		:NonDestructibleObject(scene)
		, IComposite(scene)
		, m_layer(scene)
		/*, m_z_position(z_position)*/

	{
		if (m_layer && m_layer->getRoot() && m_layer->getRoot()->getScene())
		{
			ISceneBase* layerScene = m_layer->getRoot()->getScene();
			sf::Vector2f worldSize(4000.0f, 4000.0f);

			m_shape = new RectangleSFML(worldSize.x, worldSize.y, position);
			m_shape->setTexture(layerScene->getTexture()->getTexture("j.png"));
			m_shape->getShape().setScale(1.0f, 1.0f);
		}
		else 
		{
			// Gérer l'erreur ou initialiser a minima
			std::cerr << "Erreur: pointeurs invalides dans le constructeur de Terrain" << std::endl;
		}

		
	}
	~Terrain() = default;
	float sorting_Y_point() const override
	{
		return std::numeric_limits<float>::lowest();
	}
	/*int& getZPosition()
	{
		return m_z_position;
	}*/

	void ProcessInput(const sf::Event& event) override
	{
	}
	void Update(const float& deltatime) override
	{
	}
	void Render() override
	{
		m_layer->getRoot()->getScene()->getWindow()->draw(m_shape->getShape());
	}
	
private:

	Layer* m_layer;

	/*int m_z_position;*/
	

};
enum class PlayerState
{
	DEAD
	, LIVE
	, IDLE
	, WALKING
	, RUNNING
	, ATTACK
	, CAST_SPELL
};
class Player : public DestructibleObject, public IComposite
{
public:
	Player(Layer* layer, const float& life, const sf::Vector2f& position)
		:DestructibleObject(layer, life)
		,IComposite(layer)
		, m_layer(layer)
		, m_velocity( 270.0f)
	{
		ISceneBase* layerScene = layer->getRoot()->getScene();
		
		m_shape = new RectangleSFML(48,48, position);
		m_shape->setTexture(layerScene->getTexture()->getTexture("Nova.png"));
		m_direction = { 0.0f,0.0f };
	}
	~Player() = default;
	float sorting_Y_point() const override
	{
		return  m_shape->getPosition().y + m_shape->getSize().y;
	}
	void ProcessInput(const sf::Event& event) override
	{
		
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Q:
				m_direction = { -1.0f, 0.0f };
				break;
			case sf::Keyboard::D:
				m_direction = { 1.0f, 0.0f };
				break;
			case sf::Keyboard::Z:
				m_direction = { 0.0f, -1.0f };
				break;
			case sf::Keyboard::S:
				m_direction = { 0.0f, 1.0f };
				break;
			default:
				break;
			}
			if (event.key.code == sf::Keyboard::Add) // Touche +
				m_velocity += 10.0f;
			else if (event.key.code == sf::Keyboard::Subtract) // Touche -
				m_velocity = std::max(10.0f, m_velocity - 10.0f);

			//if (event.key.code == sf::Keyboard::Add || event.key.code == sf::Keyboard::Subtract)
				//std::cout << "----------------------------------------------------"<<"Velocity changed to : " << m_velocity<<"------------------------------------" << std::endl;
			//std::cout << "Direction after key press: (" << m_direction.x << ", " << m_direction.y << ")" << std::endl;
		}

		
		else if (event.type == sf::Event::KeyReleased)
		{
			
			bool resetDirection = true;

			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Z) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				resetDirection = false;
			}

			if (resetDirection)
			{
				m_direction = { 0.0f, 0.0f };
			}
		}
	}
	void Update(const float& deltatime) override
	{
		sf::Vector2f movement = m_velocity * m_direction * deltatime;
		m_shape->setPosition(m_shape->getPosition() + movement);
	}
	void Render() override
	{
		m_layer->getRoot()->getScene()->getWindow()->draw(m_shape->getShape());

		
		RectangleSFML boundingBox(m_shape->getSize().x, m_shape->getSize().y, m_shape->getPosition());
		boundingBox.setFillColor(sf::Color::Transparent);
		boundingBox.setOutlineThickness(2);
		boundingBox.setOutlineColor(sf::Color::Green);

		
		m_layer->getRoot()->getScene()->getWindow()->draw(boundingBox.getShape());
		
		
		sf::CircleShape debugPoint(5);
		debugPoint.setFillColor(sf::Color::Red);
		sf::Vector2f anchor_point = { m_shape->getPosition().x - 5 ,m_shape->getPosition().y + 15 };
		debugPoint.setPosition(anchor_point);

		
		m_layer->getRoot()->getScene()->getWindow()->draw(debugPoint);
	}
	
private:
	Layer* m_layer;
	
	float m_velocity;
	sf::Vector2f m_direction;
	bool m_isActive;
};

enum class ZombieClassicState
{
	  DEAD
	, WALKING
	, RUNNING
	, ATTACK
	, SEEKING
	, PROWLING
	, IDLE
	, FOLLOW
};
class ZombieSeed : public DestructibleObject, public IComposite
{
private:
	Layer* m_layer;
	float m_velocity;
	sf::Vector2f m_direction;
	sf::Vector2f m_position;
	sf::Vector2f m_lastKnownPlayerPosition;

	ZombieClassicState m_currentState;
	float m_timeState;

	std::vector<sf::Vector2f> m_patrolPoints;
	size_t m_currentPatrolPoint;

	Player* m_targetPlayer;
	float m_life;
	bool m_isActive;
	std::mt19937 m_generator;
	std::bernoulli_distribution m_distribution;

public:
	ZombieSeed(Layer* layer, const float& life, const sf::Vector2f& position)
		:DestructibleObject(layer, life)
		, IComposite(layer)
		, m_layer(layer)
		, m_velocity(150.0f)
		, m_currentState(ZombieClassicState::IDLE)
		, m_timeState(0.0f)
		, m_currentPatrolPoint(0)
		, m_targetPlayer(nullptr)
		,m_life(life)
		, m_isActive(true)
		, m_position(position)
		, m_generator(std::random_device()())
		,m_distribution(0.5)
	{
		ISceneBase* layerScene = layer->getRoot()->getScene();

		m_shape = new RectangleSFML(48, 48, position);
		m_shape->setTexture(layerScene->getTexture()->getTexture("Nova.png"));
		m_direction = { 0.0f,0.0f };

		const float patrolRadius = 100.0f;

		m_patrolPoints = {
			sf::Vector2f(position.x - patrolRadius, position.y),
			sf::Vector2f(position.x, position.y - patrolRadius),
			sf::Vector2f(position.x + patrolRadius, position.y),
			sf::Vector2f(position.x, position.y + patrolRadius) 
		};
	}
	~ZombieSeed() = default;
	float sorting_Y_point() const override
	{
		return m_shape->getPosition().y + (m_shape->getSize().y / 2);
	}
	void SetActive(bool active) { m_isActive = active; }
	bool IsActive() const { return m_isActive; }
	void SetTargetPlayer(Player* player) 
	{
		m_targetPlayer = player;
	}
	void ProcessInput(const sf::Event& event) override
	{
		//COMPORTEMENT MACHINE D'ETAT
	}
	void Update(const float& deltatime) override
	{
		if (m_isActive == true)
		{
			if (m_life == 0.0f)
			{
				m_currentState = ZombieClassicState::DEAD;
				
			}
			switch (m_currentState)
			{
			case ZombieClassicState::DEAD:
				UpdateDEADState(deltatime);
				break;
			/*case ZombieClassicState::WALKING:
				UpdateWALKINGState(deltatime);
				break;
			case ZombieClassicState::RUNNING:
				UpdateRUNNINGState(deltatime);
				break;
			case ZombieClassicState::ATTACK:
				UpdateATTACKState(deltatime);
				break;*/
			/*case ZombieClassicState::SEEKING:
				UpdateSEEKINGState(deltatime);
				break;*/
			case ZombieClassicState::PROWLING:
				UpdatePROWLINGState(deltatime);
				break;
			case ZombieClassicState::IDLE:
				UpdateIDLEState(deltatime);
				break;
			case ZombieClassicState::FOLLOW:
				UpdateFOLLOWState(deltatime);
				break;
			default:
				break;
			}
			sf::Vector2f movement = m_velocity * m_direction * deltatime;
			m_shape->setPosition(m_shape->getPosition() + movement);
		}
	}
	void Render() override
	{
		if (m_isActive == true)
		{
			m_layer->getRoot()->getScene()->getWindow()->draw(m_shape->getShape());
		}
	}

private:
	void UpdateWALKINGState(const float& deltatime);
	void UpdateRUNNINGState(const float& deltatime);
	void UpdateATTACKState(const float& deltatime);
	void UpdateSEEKINGState(const float& deltatime)
	{
		std::cout << "deltatime SEEKING: " << deltatime << std::endl;
		m_timeState += deltatime;
		if (m_targetPlayer)
		{
			sf::Vector2f playerPosition = m_targetPlayer->getShape()->getPosition();
			sf::Vector2f zombiePosition = m_shape->getPosition();

			sf::Vector2f directionToPlayer = playerPosition - zombiePosition;
			float distanceToPlayer = std::sqrt(directionToPlayer.x * directionToPlayer.x
				+ directionToPlayer.y * directionToPlayer.y
			);
			if (distanceToPlayer < 200.0f)
			{
				m_currentState = ZombieClassicState::FOLLOW;
				m_timeState = 0.0f;
				return;
			}
		}
		else
		{
			if (m_timeState = 5.0f)
			{
				ZombieClassicState::PROWLING;
			}
		}
	}
	void UpdateFOLLOWState(const float& deltatime);


	void UpdateDEADState(const float& deltatime)
	{
		std::cout << "deltatime DEAD: " << deltatime << std::endl;
		m_timeState += deltatime;
		if (m_timeState >= 5.0f)
		{
			std::cout << " Je suis mouru " << std::endl;
			m_isActive = false;
			m_timeState = 0;
		}
		
	}
	void UpdateIDLEState(const float& deltatime)
	{
		std::cout << "deltatime IDLE: " << deltatime << std::endl;
		m_direction = { 0.0f,0.0f };
		m_timeState += deltatime;
		if (m_targetPlayer)
		{
			sf::Vector2f playerPosition = m_targetPlayer->getShape()->getPosition();
			sf::Vector2f zombiePosition = m_shape->getPosition();

			sf::Vector2f directionToPlayer = playerPosition - zombiePosition;
			float distanceToPlayer = std::sqrt(directionToPlayer.x * directionToPlayer.x + directionToPlayer.y * directionToPlayer.y);

			if (distanceToPlayer < 200.0f)
			{
				m_currentState = ZombieClassicState::FOLLOW;
				m_timeState = 0.0f;
			}
		}
		if (m_timeState >= 3.0f)
		{
			std::cout << "m_timeState IDLE: " << m_timeState << std::endl;
			ZombieClassicState::PROWLING;
			m_timeState = 0;
		}
	}
	
	void UpdatePROWLINGState(const float& deltatime)
	{
		std::cout << "deltatime PROWLING: " << deltatime << std::endl;
		m_timeState += deltatime;
		m_direction = m_patrolPoints.at(m_currentPatrolPoint) - m_shape->getPosition();
		float distance = std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y); 
		if (m_targetPlayer)
		{
			sf::Vector2f playerPosition = m_targetPlayer->getShape()->getPosition();
			sf::Vector2f zombiePosition = m_shape->getPosition();

			sf::Vector2f directionToPlayer = playerPosition - zombiePosition;
			float distanceToPlayer = std::sqrt(directionToPlayer.x * directionToPlayer.x
												+ directionToPlayer.y * directionToPlayer.y
			                                  );
			if (distanceToPlayer < 200.0f)
			{
				m_currentState = ZombieClassicState::FOLLOW;
				m_timeState = 0.0f;
				return;
			}
		}
		if (distance < 10.0f) 
		{
			if (m_distribution(m_generator)) 
			{
				m_currentState = ZombieClassicState::IDLE;
				m_timeState = 0.0f;
			}
			else
			{
				m_currentPatrolPoint = (m_currentPatrolPoint + 1) % m_patrolPoints.size();
			}
			
		}
		if (distance > 0) 
		{
			m_direction.x /= distance;
			m_direction.y /= distance;
		}
	}
};

class TreeTrunk : public NonDestructibleObject, public IComposite
{
public:
	TreeTrunk(Layer* layer, const sf::Vector2f& position)
		:NonDestructibleObject(layer)
		, IComposite(layer)
		, m_layer(layer)
	{
		ISceneBase* layerScene = layer->getRoot()->getScene();
		sf::Texture& treeTexture = layerScene->getTexture()->getTexture("arbre.png");

		sf::Vector2f textureSize(1200, 950);  // Taille originale
		sf::Vector2f scaleFactor(0.5f, 0.5f);  // Facteur de réduction
		sf::Vector2f spriteSize(textureSize.x * scaleFactor.x, textureSize.y * scaleFactor.y); // Taille après zoom

		// Définir un rectangle plus petit sans toucher au sprite
		sf::Vector2f rectangleSize(spriteSize.x, spriteSize.y ); // Hauteur réduite

		m_shape = new RectangleSFML(rectangleSize.x, rectangleSize.y, position + sf::Vector2f(0.0f, 125.0f));
		m_shape->setTexture(treeTexture);
		m_shape->getShape().setTextureRect(sf::IntRect(0, 950, 1200, 250));
		m_shape->getShape().setScale(scaleFactor);
		/*sf::Vector2f centerPos = layerScene->GetCenterWindow();
		sf::Vector2f treePos = centerPos + sf::Vector2f(10.0f, 0.0f);*/
		/*m_shape = new RectangleSFML(1200, 1200, position);
		m_shape->setTexture(layerGameObject->getTexture()->getTexture("arbre.png"));*/

		 /*m_shape = new RectangleSFML(1200,950, position + sf::Vector2f(0.0f, 125.0f));
		 m_shape->setTexture(layerScene->getTexture()->getTexture("arbre.png"));
		 m_shape->getShape().setTextureRect(sf::IntRect(0, 950, 1200, 250));
		 m_shape->getShape().setScale(0.25f, 0.25f);*/
	}
	~TreeTrunk() = default;
	float sorting_Y_point() const override
	{
		return m_shape->getPosition().y + m_shape->getSize().y;
	}

	void ProcessInput(const sf::Event& event) override
	{ }
	void Update(const float& deltatime) override
	{ }
	void Render() override
	{
		m_layer->getRoot()->getScene()->getWindow()->draw(m_shape->getShape());

		RectangleSFML boundingBox(m_shape->getSize().x, m_shape->getSize().y, m_shape->getPosition());
		boundingBox.setFillColor(sf::Color::Transparent);
		boundingBox.setOutlineThickness(2);
		boundingBox.setOutlineColor(sf::Color::Green);


		m_layer->getRoot()->getScene()->getWindow()->draw(boundingBox.getShape());

		// Créer un point de débogage local
		sf::CircleShape debugPoint(5);
		debugPoint.setFillColor(sf::Color::Red);
		sf::Vector2f anchor_point = { m_shape->getPosition().x - 5 ,m_shape->getPosition().y + 15 };
		debugPoint.setPosition(anchor_point);

		// Dessiner le point de débogage
		m_layer->getRoot()->getScene()->getWindow()->draw(debugPoint);
	}
private:
	Layer* m_layer;
};

class TreeLeave : public NonDestructibleObject, public ILeaf
{
public:
	TreeLeave(Layer* layer, const sf::Vector2f& position)
		:NonDestructibleObject(layer)
		, ILeaf(layer)
		, m_layer(layer)
	{
		ISceneBase* layerScene = layer->getRoot()->getScene();
		/*sf::Vector2f centerPos = layerScene->GetCenterWindow();
		sf::Vector2f treePos = centerPos + sf::Vector2f(10.0f, 0.0f);*/
		/*m_shape = new RectangleSFML(1200, 1200, position);
		m_shape->setTexture(layerGameObject->getTexture()->getTexture("arbre.png"));*/

		m_shape = new RectangleSFML(1200, 950, position + sf::Vector2f(0.0f,-110.0f));
		m_shape->setTexture(layerScene->getTexture()->getTexture("arbre.png"));
		m_shape->getShape().setTextureRect(sf::IntRect(0, 0, 1200, 950));
		m_shape->getShape().setScale(0.25f, 0.25f);
	}
	~TreeLeave() = default;

	float sorting_Y_point() const override
	{
		return m_shape->getPosition().y + m_shape->getSize().y;
	}

	void ProcessInput(const sf::Event& event) override
	{
	}
	void Update(const float& deltatime) override
	{
	}
	void Render() override
	{
		m_layer->getRoot()->getScene()->getWindow()->draw(m_shape->getShape());
	}
private:
	Layer* m_layer;
};

