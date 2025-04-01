#pragma once
#include <SFML/Graphics.hpp>

struct AABB
{
	AABB(sf::Vector2f Amin_, sf::Vector2f Amax);
	sf::Vector2f Amin;
	sf::Vector2f Amax;
};


float convertRadToDeg(const float& rad);
float convertDegToRad(const float& deg);

class IShapeSFML
{
public:
	virtual ~IShapeSFML() = default;
	virtual sf::Vector2f getSize() = 0;
	virtual sf::Vector2f getPosition() = 0;
	virtual float getangle() = 0;
	virtual sf::Shape& getShape() = 0;
	virtual void setPosition(const sf::Vector2f&) = 0;
	virtual void setSize(const sf::Vector2f&) = 0;
	virtual void setRotation(const float& angle) = 0;
	virtual void setTexture(const sf::Texture& texture) = 0;
	virtual void setCenter(sf::Vector2f) = 0;
	virtual sf::Vector2f getCenter() = 0;

	virtual AABB GetBoundingBox() = 0;

	//Débug:
	virtual void setFillColor(const sf::Color& color) = 0;
	virtual void setOutlineColor(const sf::Color& color) = 0;
	virtual void setOutlineThickness(float thickness) = 0;
};
class RectangleSFML : public IShapeSFML
{
public:
	RectangleSFML(float width, float height, sf::Vector2f position, sf::Vector2f Origin);

	RectangleSFML(float width, float height, sf::Vector2f position);


	sf::Vector2f getPosition() override;

	sf::Vector2f getSize() override;

	float getangle() override;

	void setTexture(const sf::Texture& texture) override;

	void setPosition(const sf::Vector2f& position) override;

	void setSize(const sf::Vector2f& size)override;

	void setRotation(const float& angle) override;

	void setCenter(sf::Vector2f) override;
	sf::Vector2f getCenter() override;

	sf::Shape& getShape() override;

	 AABB GetBoundingBox()override;

	 //Débug:
	 void setFillColor(const sf::Color& color) override;
	 void setOutlineColor(const sf::Color& color) override;
	 void setOutlineThickness(float thickness) override;

protected:
	sf::RectangleShape m_shape;
};

class SquareSFML : public RectangleSFML
{
public:
	SquareSFML(float size, sf::Vector2f position, sf::Vector2f Origin);

	SquareSFML(float size, sf::Vector2f position);

	sf::Shape& getShape() override;

};

class CircleSFML : public IShapeSFML
{
public:
	CircleSFML(float r, sf::Vector2f position, sf::Vector2f Origin);

	CircleSFML(float r, sf::Vector2f position);

	sf::Vector2f getPosition() override;

	sf::Vector2f getSize() override;

	float getangle() override;

	void setTexture(const sf::Texture& texture) override;

	void setPosition(const sf::Vector2f& position) override;

	void setSize(const sf::Vector2f& size)override;

	void setRotation(const float& angle) override;

	void setCenter(sf::Vector2f) override;
	sf::Vector2f getCenter() override;

	sf::Shape& getShape() override;
	AABB GetBoundingBox()override;

protected:
	sf::CircleShape m_shape;
};

