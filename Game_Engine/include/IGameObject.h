#pragma once
#include "Layer.h"


//Si je dois changer ça, veut dire GROSSE FEATURE
enum class GameObjectType : uint32_t
{
	 Visibility		 = 0b0001  // 1=Visible, 0=Invisible
	,Destructibility = 0b0010  // 1=Destructible, 0=Indestructible
	,Component		 = 0b0100  // 1=Container, 0=Leaf
	,Hitbox			 = 0b1000  // 1=Has hitbox, 0=No hitbox
};


inline GameObjectType operator | (GameObjectType lhs, GameObjectType rhs);
inline GameObjectType operator & (GameObjectType lhs, GameObjectType rhs);
inline GameObjectType operator ^ (GameObjectType lhs, GameObjectType rhs);
inline GameObjectType operator ~ (GameObjectType value);

class Reader_GameObjectType 
{
public:
	explicit Reader_GameObjectType(uint32_t rawValue)
		: m_rawValue(rawValue)
	{}

	bool hasHitbox() const;

	bool isVisible() const;

	bool isContainer() const;

	bool isLeaf() const;
	
	bool isDestructible() const;

private:
	uint32_t m_rawValue;
};


class IGameObject : public IComponent
{
public:
	IGameObject(IComposite* parent = nullptr)
		:IComponent(nullptr)
	{}
	virtual ~IGameObject() = default;


	virtual void Update(const float& deltatime) = 0;
	virtual void ProcessInput(const sf::Event& event) = 0;
	virtual void Render() = 0;


	virtual uint32_t getGameObjectType() const = 0;
	virtual LayersType getLayersType() const = 0;
	virtual sf::Vector2f getInitPosition() const;
	virtual sf::Vector2f getCurrentPosition() const;
	virtual float sorting_Y_point() const;
protected:
	const sf::Vector2f m_initialPosition{ 0, 0 };
	sf::Vector2f m_currentPosition{ 0, 0 };
};




#define DECLARE_GAME_OBJECT()      \
uint32_t getGameObjectType() const override; \
LayersType getLayersType() const override; \
sf::Vector2f getInitPosition() const override; \
sf::Vector2f getCurrentPosition() const override; \
const sf::Vector2f m_initialPosition; \
sf::Vector2f m_currentPosition;

#define DEFINE_GAME_OBJECT(TheClassName,InitPosition,layer,TypeGameObject) \
sf::Vector2f TheClassName::getInitPosition() const { return InitPosition; } \
::LayersType TheClassName::getLayersType() const { return layer; } \
uint32_t TheClassName::getGameObjectType() const { return TypeGameObject; } \
sf::Vector2f TheClassName::getCurrentPosition() const { return m_currentPosition; } 
