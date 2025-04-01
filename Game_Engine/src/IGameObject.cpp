#include "IGameObject.h"

inline GameObjectType operator | (GameObjectType lhs, GameObjectType rhs)
{
	return static_cast<GameObjectType>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}
inline GameObjectType operator & (GameObjectType lhs, GameObjectType rhs)
{
	return static_cast<GameObjectType>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}
inline GameObjectType operator ^ (GameObjectType lhs, GameObjectType rhs)
{
	return static_cast<GameObjectType>(static_cast<uint32_t>(lhs) ^ static_cast<uint32_t>(rhs));
}
inline GameObjectType operator ~ (GameObjectType value)
{
	return static_cast<GameObjectType>(~static_cast<uint32_t>(value));
}

bool Reader_GameObjectType::hasHitbox() const
{
	return (m_rawValue & static_cast<uint32_t>(GameObjectType::Hitbox)) != 0;
}

bool Reader_GameObjectType::isVisible() const
{
	return (m_rawValue & static_cast<uint32_t>(GameObjectType::Visibility)) != 0;
}

bool Reader_GameObjectType::isContainer() const
{
	return (m_rawValue & static_cast<uint32_t>(GameObjectType::Component)) != 0;
}

bool Reader_GameObjectType::isLeaf() const
{
	return !isContainer();
}

bool Reader_GameObjectType::isDestructible() const
{
	return (m_rawValue & static_cast<uint32_t>(GameObjectType::Destructibility)) != 0;
}


sf::Vector2f IGameObject::getInitPosition() const 
{ 
	return m_initialPosition; 
}
sf::Vector2f IGameObject::getCurrentPosition() const 
{ 
	return m_currentPosition; 
}
float IGameObject::sorting_Y_point() const
{ 
	return 0.0f; 
}