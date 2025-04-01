#pragma once
#include <SFML/Graphics.hpp>
#include "IGameObject.h"
#include "SpriteSheet.h"
#include "IShape.h"
#include "SceneBase.h"


class Player : public IGameObject
{

public:
	DECLARE_GAME_OBJECT()
	Player(const sf::Vector2f& initposition, TextureCache& textureCache)
		: m_initialPosition(initposition)
		, m_currentPosition(initposition)
		, m_textureCache(textureCache)
		, m_velocity(100.0f)  
		, m_direction(0.0f, 0.0f)
		//, m_SpriteSheet(new AnimatedSpriteSheet(&textureCache,(528,624)))
		
	{
		//m_SpriteSheet->addRegion({0,0},)
		m_shape = new RectangleSFML(48, 48, m_currentPosition);
	}
	virtual ~Player()
	{
		delete m_shape;
	}
	float sorting_Y_point() const
	{
		return  m_shape->getPosition().y + m_shape->getSize().y;
	}
	
	void Update(const float& deltatime) override
	{
		sf::Vector2f movement = m_velocity * m_direction * deltatime;
		m_shape->setPosition(m_shape->getPosition() + movement);
		//m_sprite.setPosition(m_shape->getPosition());  
		m_currentPosition = m_shape->getPosition();
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
	void Render() override
	{
		Layer* layer = static_cast<Layer*>(getParent());
		ISceneBase* scene = static_cast<ISceneBase*>(layer->getParent());
		//scene->getWindow()->draw(m_sprite);
		

		RectangleSFML boundingBox(m_shape->getSize().x, m_shape->getSize().y, m_shape->getPosition());
		boundingBox.setFillColor(sf::Color::Transparent);
		boundingBox.setOutlineThickness(2);
		boundingBox.setOutlineColor(sf::Color::Green);

		scene->getWindow()->draw(boundingBox.getShape());


		sf::CircleShape debugPoint(5);
		debugPoint.setFillColor(sf::Color::Red);
		sf::Vector2f anchor_point = { m_shape->getPosition().x - 5 ,m_shape->getPosition().y + 15 };
		debugPoint.setPosition(anchor_point);

		scene->getWindow()->draw(debugPoint);
	}
private:
	AnimatedSpriteSheet* m_SpriteSheet;
	TextureCache& m_textureCache;
	IShapeSFML* m_shape;

	float m_velocity;
	sf::Vector2f m_direction;
};


//void ProcessInput(const sf::Event& event) override
//{
//
//	
//}
//void Update(const float& deltatime) override
//{
//	
//}
//void Render() override
//{
//	
//}
//
//private:
//	Layer* m_layer;
//
//	
//	bool m_isActive;