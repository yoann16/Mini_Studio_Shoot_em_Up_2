#pragma once
#include <random>
#include <SFML/System/Vector2.hpp>

class RandomNumber
{
public:
	RandomNumber();
	~RandomNumber() = default;

	template<typename type = int>
    type getRandomNumber(type min, type max)
    {
        std::uniform_int_distribution<type> dis(min, max);
        return dis(m_gen);
    }
private:
    std::random_device m_rd;
    std::mt19937 m_gen;
};

RandomNumber& UseRandomNumber();

struct Vec2
{
	Vec2(sf::Vector2f Amin_, sf::Vector2f Amax);
	sf::Vector2f Pmin;
	sf::Vector2f Pmax;
};

enum class SpanwPosition
{
	Left
	,Up
	,Down
	,Right
};

class RandomSpanw
{
public:
	static sf::Vector2f getPosition(Vec2 zone, const sf::Vector2f& size);
	static sf::Vector2f getPosition(Vec2 zone, Vec2 RestrictedArea , const sf::Vector2f& size);
	static sf::Vector2f getPosition(Vec2 zone, SpanwPosition position , const sf::Vector2f& size);
};

