#pragma once
#include "IGameObject.h"
#include "IShape.h"
#include "KT_Math_Algorithm.h"
#include "KT_Array.h"
#include "KT_VectorND.h"
#include <iostream>

class Player : public DestructibleObject, public IComposite
{
public:
	Player(IComposite* scene, const float& life, sf::Vector2f& positioninit)
		:DestructibleObject(scene,100)
		,IComposite(scene)
		, m_velocity( 270.0f)
	{
		positioninit = m_scene->getRoot()->getScene()->GetCenterWindow();
		
		m_shape = new RectangleSFML(48,48, scene->getRoot()->getScene());
		m_shape->setTexture( m_scene->getRoot()->getScene()->getTexture()->getTexture("Nova.png"));
		m_direction = { 0,0 };
	}
	~Player()=default;
	void ProcessInput(const sf::Event& event) override
	{
		
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Q:
				m_direction = { -1, 0 };
				break;
			case sf::Keyboard::D:
				m_direction = { 1, 0 };
				break;
			case sf::Keyboard::Z:
				m_direction = { 0, -1 };
				break;
			case sf::Keyboard::S:
				m_direction = { 0, 1 };
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
				m_direction = { 0, 0 };
				//std::cout << "Direction after reset: (" << m_direction.x << ", " << m_direction.y << ")" << std::endl;
			}
		}
	}
	void Update(const float& deltatime) override
	{
		//std::cout << "Direction before reset: (" << m_direction.x << ", " << m_direction.y << ")" << std::endl;
		//float deltaTimeSeconds = deltatime / 1000.0f;
		sf::Vector2f movement = m_velocity * m_direction * deltatime;
		m_shape->setPosition(m_shape->getPosition() + movement);
		/*std::cout << "DeltaTime: " << deltatime << " seconds" << std::endl;
		std::cout << "Direction: (" << m_direction.x << ", " << m_direction.y << ")" << std::endl;
		std::cout << "Movement: (" << movement.x << ", " << movement.y << ")" << std::endl;*/
		

	}
	void Render() override
	{
		m_scene->getRoot()->getScene()->getWindow()->draw(m_shape->getShape());
	}
private:
	float m_velocity;
	sf::Vector2f m_direction;
};