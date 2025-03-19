#include "RandomNumber.h"

RandomNumber::RandomNumber() :m_gen(m_rd())
{}

RandomNumber& UseRandomNumber()
{
	static RandomNumber rd;
	return rd;
}



Vec2::Vec2(sf::Vector2f Amin_, sf::Vector2f Amax) : Pmin(Amin_), Pmax(Amax) {}

sf::Vector2f RandomSpanw::getPosition(Vec2 zone, const sf::Vector2f& size)
{
	auto x = UseRandomNumber().getRandomNumber<int>(zone.Pmin.x + size.x, zone.Pmax.x - size.x);
	auto y = UseRandomNumber().getRandomNumber<int>(zone.Pmin.y + size.y, zone.Pmax.y - size.y);
	sf::Vector2f result = sf::Vector2f(x, y);
	return result;

}

sf::Vector2f RandomSpanw::getPosition(Vec2 zone, Vec2 RestrictedArea ,const  sf::Vector2f& size)
{
	auto x = UseRandomNumber().getRandomNumber<int>(zone.Pmin.x + size.x, zone.Pmax.x - size.x);
	auto y = UseRandomNumber().getRandomNumber<int>(zone.Pmin.y + size.y, zone.Pmax.y - size.y);
	sf::Vector2f result = sf::Vector2f(x, y);
	while (result.x > RestrictedArea.Pmin.x -size.x && result.x < RestrictedArea.Pmax.x + size.x && result.y > RestrictedArea.Pmin.y - size.y && result.y < RestrictedArea.Pmax.y + size.y)
	{
		result.x = UseRandomNumber().getRandomNumber<int>(zone.Pmin.x + size.x, zone.Pmax.x - size.x);
		result.y = UseRandomNumber().getRandomNumber<int>(zone.Pmin.y + size.y, zone.Pmax.y - size.y);
	}
	return result;

}

sf::Vector2f RandomSpanw::getPosition(Vec2 zone, SpanwPosition position ,  const sf::Vector2f& size)
{
	auto x = 0;
	auto y = 0;
	sf::Vector2f result = sf::Vector2f(x, y);

	switch (position)
	{
	case SpanwPosition::Left:
		{
		result.x = zone.Pmin.x + size.x;
		result.y = UseRandomNumber().getRandomNumber<int>(zone.Pmin.y + size.y, zone.Pmax.y - size.y);
		}
		break;
	case SpanwPosition::Right:
		{
		result.x = zone.Pmax.x - size.x;
			result.y = UseRandomNumber().getRandomNumber<int>(zone.Pmin.y + size.y, zone.Pmax.y - size.y);
		}
		break;
	case SpanwPosition::Up:
		{

		result.y = zone.Pmin.y + size.y;
		result.x = UseRandomNumber().getRandomNumber<int>(zone.Pmin.x + size.x, zone.Pmax.x - size.x);
		}
		break;
	case SpanwPosition::Down:
		{
		result.x = UseRandomNumber().getRandomNumber<int>(zone.Pmin.x + size.x, zone.Pmax.x - size.x);
		result.y = zone.Pmax.y - size.y;
		}
		break;
	}
	return  result;
}
