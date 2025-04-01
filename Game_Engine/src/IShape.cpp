#include "IShape.h"

AABB::AABB(sf::Vector2f Amin_, sf::Vector2f Amax)
	: Amin(Amin_)
	, Amax(Amax)
{
}


float convertRadToDeg(const float& rad)
{
	return (180 * rad) / 3.14159f;
}

float convertDegToRad(const float& deg)
{
	return (deg * 3.14159f) / 180;
}

RectangleSFML::RectangleSFML(float width, float height, sf::Vector2f position, sf::Vector2f Origin) :m_shape(sf::Vector2f(width, height))
{
	m_shape.setPosition(position);
	m_shape.setOrigin(Origin);
}

RectangleSFML::RectangleSFML(float width, float heignt, sf::Vector2f position) :m_shape(sf::Vector2f(width, heignt))
{
	m_shape.setPosition(position);
	m_shape.setOrigin(m_shape.getSize().x / 2, m_shape.getSize().y / 2);
}



sf::Shape& RectangleSFML::getShape()
{
	return static_cast<sf::Shape&>(m_shape);
}

AABB RectangleSFML::GetBoundingBox()
{
	AABB boundingbox{sf::Vector2f(0,0),sf::Vector2f(0,0) };
	boundingbox.Amin.x = m_shape.getPosition().x - m_shape.getSize().x / 2;
	boundingbox.Amin.y = m_shape.getPosition().y - m_shape.getSize().y / 2;

	boundingbox.Amax.x = m_shape.getPosition().x + m_shape.getSize().x / 2;
	boundingbox.Amax.y = m_shape.getPosition().y + m_shape.getSize().y / 2;

	
	return boundingbox;
}

sf::Vector2f RectangleSFML::getPosition()
{
	return m_shape.getPosition();
}

sf::Vector2f RectangleSFML::getSize()
{
	return m_shape.getSize();
}

float RectangleSFML::getangle()
{
	return m_shape.getRotation();
}

void RectangleSFML::setTexture(const sf::Texture& texture)
{
	m_shape.setTexture(&texture);
}

void RectangleSFML::setPosition(const sf::Vector2f& position)
{
	m_shape.setPosition(position);
}

void RectangleSFML::setSize(const sf::Vector2f& size)
{
	m_shape.setSize(size);
}

void RectangleSFML::setRotation(const float& angle)
{
	m_shape.setRotation(angle);
}

void RectangleSFML::setCenter(sf::Vector2f vec)
{
	m_shape.setOrigin(vec);
}

sf::Vector2f RectangleSFML::getCenter()
{
	return m_shape.getOrigin();
}

//Débug:
void RectangleSFML::setFillColor(const sf::Color& color) { m_shape.setFillColor(color); };
void RectangleSFML::setOutlineColor(const sf::Color& color) { m_shape.setOutlineColor(color); };
void RectangleSFML::setOutlineThickness(float thickness) { m_shape.setOutlineThickness(thickness); };




SquareSFML::SquareSFML(float size, sf::Vector2f position, sf::Vector2f Origin) :RectangleSFML(size, size, position, Origin)
{
	m_shape.setPosition(position);
	m_shape.setOrigin(Origin);
}

SquareSFML::SquareSFML(float size, sf::Vector2f position) :RectangleSFML(size, size, position)
{
	m_shape.setPosition(position);
	m_shape.setOrigin(m_shape.getSize().x / 2, m_shape.getSize().y / 2);
}

sf::Shape& SquareSFML::getShape()
{
	return static_cast<sf::Shape&>(m_shape);
}

CircleSFML::CircleSFML(float r, sf::Vector2f position, sf::Vector2f Origin) :m_shape(r)
{
	m_shape.setPosition(sf::Vector2f(position));
	m_shape.setOrigin(Origin);
}

CircleSFML::CircleSFML(float r, sf::Vector2f position) :m_shape(r)
{
	m_shape.setPosition(position);
	m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
}

sf::Shape& CircleSFML::getShape()
{
	return static_cast<sf::Shape&>(m_shape);
}

AABB CircleSFML::GetBoundingBox()
{
	AABB boundingbox{ sf::Vector2f(0,0),sf::Vector2f(0,0) };
	boundingbox.Amin.x = m_shape.getPosition().x - m_shape.getRadius();
	boundingbox.Amin.y = m_shape.getPosition().y - m_shape.getRadius();

	boundingbox.Amax.x = m_shape.getPosition().x + m_shape.getRadius();
	boundingbox.Amax.y = m_shape.getPosition().y + m_shape.getRadius();

	return boundingbox;
}

sf::Vector2f CircleSFML::getPosition()
{
	return m_shape.getPosition();
}

sf::Vector2f CircleSFML::getSize()
{
	return sf::Vector2f{ m_shape.getRadius() * 2, m_shape.getRadius() * 2 };
}

float CircleSFML::getangle()
{
	return m_shape.getRotation();
}

void CircleSFML::setTexture(const sf::Texture& texture)
{
	m_shape.setTexture(&texture);
}

void CircleSFML::setPosition(const sf::Vector2f& position)
{
	m_shape.setPosition(position);
}

void CircleSFML::setSize(const sf::Vector2f& size)
{
	if (size.x != size.y)
		throw std::runtime_error("Size must be equal");
	m_shape.setRadius(size.x / 2);
}

void CircleSFML::setRotation(const float& angle)
{
	m_shape.setRotation(angle);
}

void CircleSFML::setCenter(sf::Vector2f vec)
{
	m_shape.setOrigin(vec);
}
sf::Vector2f CircleSFML::getCenter()
{
	return m_shape.getOrigin();
}