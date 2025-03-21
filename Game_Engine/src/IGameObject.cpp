#include "IGameObject.h"
#include "SceneBase.h"
#include "IShape.h"
#include <iostream>

AABB::AABB(sf::Vector2f Amin_, sf::Vector2f Amax) : Amin(Amin_), Amax(Amax) {}


float convertRadToDeg(const float& rad)
{
	return (180 * rad) / 3.14159f;
}

float convertDegToRad(const float& deg)
{
	return (deg * 3.14159f) / 180;
}

IGameObject::IGameObject(IComposite* scene):m_scene(scene),m_needDestroy(false), m_sprite(nullptr)
{

}

IGameObject::~IGameObject()
{
	delete m_shape;
	if (m_sprite != nullptr) 
	{
		delete m_sprite;
	}
}

AABB IGameObject::GetBoundingBox()
{
	return m_shape->GetBoundingBox();
}

IShapeSFML* IGameObject::getShape()
{
	return m_shape;
}
IShapeSFML* IGameObject::getShape() const
{
	return m_shape;
}

bool IGameObject::NeedDestroy()
{
	return m_needDestroy;
}

void IGameObject::destroy()
{
	m_needDestroy = true;
}


DestructibleObject::DestructibleObject(IComposite* scene, const float& life) 
	:IGameObject(scene)
	, m_life(life)
{
}

GameObjectType DestructibleObject::globalGameObjectType()
{
	return GameObjectType::DestructibleObject;
}

NonDestructibleObject::NonDestructibleObject(IComposite* scene) :IGameObject(scene)
{
}

GameObjectType NonDestructibleObject::globalGameObjectType()
{
	return GameObjectType::NonDestructibleObject;
}


IComponent::IComponent(IComposite* parent) :m_parent(nullptr)
{
	setParent(parent);
}

IComponent::~IComponent()
{
	setParent(nullptr);
}

IComponent* IComponent::getParent()
{
	return m_parent;
}

const IComponent* IComponent::getParent() const
{
	return m_parent;
}


void IComponent::setParent(IComposite* parent)
{
	if (m_parent)
		m_parent->remove(this);

	m_parent = parent;

	if (m_parent)
		m_parent->add(this);
}

RootScene* IComponent::getRoot()
{
	auto* curent = this;
	while (curent->getParent() != nullptr)
	{
		curent = curent->getParent();
	}
	return static_cast<RootScene*>(curent);
}

const RootScene* IComponent::getRoot() const
{
	auto* curent = this;
	while (curent->getParent() != nullptr)
	{
		curent = curent->getParent();
	}
	return static_cast<const RootScene*>(curent);
}

IComposite::IComposite(IComposite* parent) : IComponent(parent)
{

}
void IComposite::Update(const float& deltatime)
{
	for (auto& child : m_children)
		child->Update(deltatime);
}

void IComposite::ProcessInput(const sf::Event& event)
{
	for (auto& child : m_children)
		child->ProcessInput(event);
}


void IComposite::Render()
{
	for (auto& child : m_children)
		child->Render();
}


IComposite::~IComposite()
{
	for (std::make_signed_t<size_t> i = m_children.Size() - 1; i >= 0; --i)
	{
		delete m_children[i];
	}
	m_children.clear();
}



KT::Vector<IComponent*> IComposite::getChildren()
{
	return m_children;
}

const KT::Vector<IComponent*> IComposite::getChildren() const
{
	return m_children;
}

//KT::Vector<IComponant*> IComposite::IterateAllComposite()
//{
//	KT::Vector<IComponant*> result;
//	for (auto child : getChildren())
//	{
//		m_shildren.pushBack(child);
//		if (child->GetComponantType() == Componant::IComposite)
//		{
//			for (auto childchild : static_cast<IComposite*>(child)->getChildren())
//			{
//				
//			}
//		}
//	}
//}

void IComposite::add(IComponent* data)
{
	m_children.pushBack(data);
}

void IComposite::remove(IComponent* data)
{
	auto it = std::find(m_children.begin(), m_children.end(), data);
	if (it == m_children.end())
		throw;
	m_children.erase(it);
}

RootScene::RootScene(ISceneBase* scene)
	:IComposite(nullptr)
	,m_scene(scene)
{

}

KT::Vector<IComponent*> IComposite::getFullTree()
{
	KT::Vector<IComponent*> Result;
	AddFullTree(Result, getChildren());
	return Result;
}

ISceneBase* RootScene::getScene()
{
	return m_scene;
}

void IComposite::AddFullTree(KT::Vector<IComponent*>& toAdd, KT::Vector<IComponent*> iterate)
{
	for (auto it : iterate)
	{
		toAdd.pushBack(it);
		if (it->GetComponentType() == Component::IComposite)
		{
			AddFullTree(toAdd, static_cast<IComposite*>(it)->getChildren());
		}
	}
}


ILeaf::ILeaf(IComposite* parent) :IComponent(parent)
{
}


