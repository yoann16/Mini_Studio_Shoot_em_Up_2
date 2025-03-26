#pragma once
#include "IGameObject.h"
#include "IShape.h"
#include "KT_Math_Algorithm.h"
#include "KT_Array.h"
#include "KT_VectorND.h"
#include "TextureCache.h"
#include <iostream>


class Player : public DestructibleObject, public IComposite
{
public:
    Player(IComposite* scene, const float& life, sf::Vector2f& positioninit)
        : DestructibleObject(scene, 100)
        , IComposite(scene)
        , m_velocity(270.0f)
    {
        positioninit = m_scene->getRoot()->getScene()->GetCenterWindow();

        m_shape = new RectangleSFML(48, 48, scene->getRoot()->getScene());

        sf::Texture& spriteTexture = m_scene->getRoot()->getScene()->getTexture()->getTexture("spritesheet.png");

        m_animatedSprite = new AnimatedSprite(positioninit, spriteTexture);

        m_direction = { 0, 0 };
        m_isMoving = false;
    }

    ~Player()
    {
        delete m_animatedSprite;
    }

    void ProcessInput(const sf::Event& event) override
    {
        if (event.type == sf::Event::KeyPressed)
        {
            bool dirChanged = false;

            switch (event.key.code)
            {
            case sf::Keyboard::Q:  
                m_direction = { -1, 0 };
                dirChanged = true;
                break;
            case sf::Keyboard::D:  
                m_direction = { 1, 0 };
                dirChanged = true;
                break;
            case sf::Keyboard::Z: 
                m_direction = { 0, -1 };
                dirChanged = true;
                break;
            case sf::Keyboard::S:  
                m_direction = { 0, 1 };
                dirChanged = true;
                break;
            default:
                break;
            }

            if (dirChanged) {
                m_isMoving = true;
                m_animatedSprite->SetDirection(m_direction);
            }

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
                m_isMoving = false;
                m_animatedSprite->SetDirection(m_direction); 
            }
        }
    }

    sf::Vector2f GetPosition() const
    {
        return m_shape->getPosition();
    }

    void Update(const float& deltatime) override
    {
        sf::Vector2f movement = m_velocity * m_direction * deltatime;
        sf::Vector2f newPosition = m_shape->getPosition() + movement;
        m_shape->setPosition(newPosition);
        m_animatedSprite->SetPosition(newPosition);
        m_animatedSprite->Update(deltatime);
    }

    void Render() override
    {
        m_animatedSprite->Draw(*m_scene->getRoot()->getScene()->getWindow());
    }

private:
    float m_velocity;
    sf::Vector2f m_direction;
    AnimatedSprite* m_animatedSprite;
    bool m_isMoving;
};