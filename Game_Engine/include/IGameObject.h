#pragma once
#include <KT_Vector.h>
#include "IGameObject.h"
#include "IGameObject.h"
#include <SFML/Graphics.hpp>

struct AABB
{
	AABB(sf::Vector2f Amin_, sf::Vector2f Amax);
	sf::Vector2f Amin;
	sf::Vector2f Amax;
};


float convertRadToDeg(const float& rad);
float convertDegToRad(const float& deg);

class IShapeSFML;
class RootScene;
class ISceneBase;
class IComposite;

enum class Component
{
	IComposite
	,ILeaf
	,IGameObject
};


class IComponent
{
public:
	IComponent(IComposite* parent );
	virtual ~IComponent();
	IComponent* getParent();
	 const IComponent* getParent() const;

	virtual void Update(const float& deltatime) = 0;
	virtual void ProcessInput(const sf::Event& event) = 0;
	virtual void Render() = 0;
	virtual Component GetComponentType() = 0;
	virtual const Component GetComponentType() const = 0;
	 RootScene* getRoot();
	 const RootScene* getRoot() const;

	void setParent(IComposite* parent);
protected:
	
	IComposite* m_parent;
};


class IComposite : public IComponent
{
public:
	friend IComponent;

	IComposite(IComposite* parent );
	~IComposite();

	 void Update(const float& deltatime)override;
	 void ProcessInput(const sf::Event& event)override;
	 void Render()override;
	 KT::Vector<IComponent*> getChildren();
	 const KT::Vector<IComponent*> getChildren() const;
	 KT::Vector<IComponent*> getFullTree();
protected:

	//KT::Vector<IComponant*> IterateAllComposite();
	//const KT::Vector<IComponant*> IterateAllComposite() const;

	Component GetComponentType() override
	 {
		 return Component::IComposite;
	 }
	 const Component GetComponentType() const override
	{
		 return Component::IComposite;
	}
private:
	void add(IComponent* data);
	void remove(IComponent* data);
	void AddFullTree(KT::Vector<IComponent*>& toAdd, KT::Vector<IComponent*> iterate);
	KT::Vector<IComponent*> m_children;
};

class RootScene : public IComposite
{
public:
	RootScene(ISceneBase* scene);
	
	ISceneBase* getScene();
private:

	ISceneBase* m_scene;
};

class ILeaf : public IComponent
{
public:
	ILeaf(IComposite* parent);

	virtual void Update(const float& deltatime) = 0;
	virtual void ProcessInput(const sf::Event& event) = 0;
	virtual void Render() = 0;

	Component GetComponentType() override
	{
		return Component::ILeaf;
	}
	const Component GetComponentType() const override
	{
		return Component::ILeaf;
	}
};
enum class GameObjectType
{
	DestructibleObject
	,NonDestructibleObject
};

class IGameObject 
{
public:
	IGameObject(IComposite* scene);
	virtual ~IGameObject();

	virtual void Update(const float& deltatime) = 0;
	virtual void ProcessInput(const sf::Event& event) = 0;
	virtual void Render() = 0;
	virtual AABB GetBoundingBox();
	IShapeSFML* getShape();
	IShapeSFML* getShape() const;
	virtual GameObjectType globalGameObjectType() = 0;
	virtual void HandleCollision(IGameObject* object){}
	virtual float sorting_Y_point() const = 0;
	bool NeedDestroy();

	void destroy();

protected:
	IComposite* m_scene;
	IShapeSFML* m_shape;
	sf::Sprite* m_sprite;
private:
	bool m_needDestroy;
};

class DestructibleObject : public IGameObject
{
public:
	DestructibleObject(IComposite* scene, const float& life);

	void Update(const float& deltatime) override = 0;
	void ProcessInput(const sf::Event& event) override = 0;
	void Render() = 0;

	virtual void ChangeLife(const float& life)
	{
		m_life += life;
		if (m_life <= 0)
			destroy();
	}
	float getCurrentLife() { return m_life; }
	
	 GameObjectType globalGameObjectType() override;
protected:
	float m_life;
};

class NonDestructibleObject : public IGameObject
{
public:
	NonDestructibleObject(IComposite* scene);

	void Update(const float& deltatime) override = 0;
	void ProcessInput(const sf::Event& event) override = 0;
	void Render() = 0;
	 GameObjectType globalGameObjectType() override;
};

template<typename type , typename type2>
type getObj(type2* obj)
{
	return dynamic_cast<type>(obj);
}