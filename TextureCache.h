#pragma once
#include "KT_Vector.h"
#include <string>
#include <SFML/Graphics.hpp>

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

class AnimatedSprite
{
public:
    AnimatedSprite(const sf::Vector2f& pos, sf::Texture& texture)
        : m_position(pos), m_currentFrame(0), m_currentRow(0),
        m_frameSize(48, 48), m_animTime(0.0f), m_frameDuration(0.1f)
    {
        m_sprite = sf::Sprite(texture);
        m_sprite.setPosition(m_position);
        m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameSize.x, m_frameSize.y));
    }

    void Draw(sf::RenderTarget& rt) const
    {
        rt.draw(m_sprite);
    }

    void SetPosition(const sf::Vector2f& pos)
    {
        m_position = pos;
        m_sprite.setPosition(m_position);
    }

    void SetDirection(const sf::Vector2f& dir)
    {
        m_velocity = dir * m_speed;


        if (dir.x != 0 || dir.y != 0) {
            m_lastDirection = dir;
        }

        if (dir.x < 0) // Gauche
            m_targetRow = 2;
        else if (dir.x > 0) // Droite
            m_targetRow = 1;
        else if (dir.y < 0) // Haut
            m_targetRow = 3;
        else if (dir.y > 0) // Bas
            m_targetRow = 0;
        else {

            m_isIdle = true;
            return;
        }

        m_isIdle = false;
        m_currentRow = m_targetRow;
        UpdateTextureRect();
    }

    void Update(float dt)
    {
        m_position += m_velocity * dt;
        m_sprite.setPosition(m_position);

        if (m_isIdle) {
            return;
        }


        m_animTime += dt;
        if (m_animTime >= m_frameDuration)
        {
            m_animTime -= m_frameDuration;
            m_currentFrame = (m_currentFrame + 1) % m_framesPerRow;
            UpdateTextureRect();
        }
    }

    void UpdateTextureRect()
    {

        int xOffset = 0;
        int yOffset = 0;

        if (m_currentRow == 1) yOffset = 2;
        if (m_currentRow == 2) yOffset = 4;
        if (m_currentRow == 3) yOffset = 6;

        m_sprite.setTextureRect(sf::IntRect(
            m_currentFrame * m_frameSize.x + xOffset,
            m_currentRow * m_frameSize.y + yOffset,
            m_frameSize.x,
            m_frameSize.y
        ));
    }

private:
    static constexpr float m_speed = 3.0f;
    sf::Vector2f m_position;
    sf::Vector2f m_velocity = { 0.0f, 0.0f };
    sf::Vector2f m_lastDirection = { 0.0f, 1.0f };
    sf::Sprite m_sprite;

    sf::Vector2i m_frameSize;
    int m_currentFrame;
    int m_currentRow;
    int m_targetRow;
    int m_framesPerRow = 8;
    float m_animTime;
    float m_frameDuration;
    bool m_isIdle = false;
};