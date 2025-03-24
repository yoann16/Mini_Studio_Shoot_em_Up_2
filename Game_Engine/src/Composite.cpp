#include "Composite.h"

IComponent::IComponent(IComposite* parent) 
	:m_parent(nullptr)
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

Root* IComponent::getRoot()
{
	auto* curent = this;
	while (curent->getParent() != nullptr)
	{
		curent = curent->getParent();
	}
	return static_cast<Root*>(curent);
}

const Root* IComponent::getRoot() const
{
	auto* curent = this;
	while (curent->getParent() != nullptr)
	{
		curent = curent->getParent();
	}
	return static_cast<const Root*>(curent);
}

IComposite::IComposite(IComposite* parent) 
	: IComponent(parent)
{

}
//void IComposite::Update(const float& deltatime)
//{
//	for (auto& child : m_children)
//		child->Update(deltatime);
//}
//
//void IComposite::ProcessInput(const sf::Event& event)
//{
//	for (auto& child : m_children)
//		child->ProcessInput(event);
//}
//
//
//void IComposite::Render()
//{
//	for (auto& child : m_children)
//		child->Render();
//}


IComposite::~IComposite()
{
	for (std::make_signed_t<size_t> i = m_children.size() - 1; i >= 0; --i)
	{
		delete m_children[i];
	}
	m_children.clear();
}


std::vector<IComponent*> IComposite::getChildren()
{
	return m_children;
}

const std::vector<IComponent*> IComposite::getChildren() const
{
	return m_children;
}

void IComposite::add(IComponent* data)
{
	m_children.push_back(data);
}

void IComposite::remove(IComponent* data)
{
	auto it = std::find(m_children.begin(), m_children.end(), data);
	if (it == m_children.end())
		throw;
	m_children.erase(it);
}

//std::vector<IComponent*> IComposite::getFullTree()
//{
//	std::vector<IComponent*> Result;
//	AddFullTree(Result, getChildren());
//	return Result;
//}
//
//void IComposite::AddFullTree(std::vector<IComponent*>& toAdd, std::vector<IComponent*> iterate)
//{
//	for (auto it : iterate)
//	{
//		toAdd.push_back(it);
//		if (it->GetComponentType() == Component::IComposite)
//		{
//			AddFullTree(toAdd, static_cast<IComposite*>(it)->getChildren());
//		}
//	}
//}


ILeaf::ILeaf(IComposite* parent) 
	:IComponent(parent)
{
}

Root::Root()
	:IComposite(nullptr)
{
	
}

