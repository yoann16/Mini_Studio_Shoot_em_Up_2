#include "Layer.h"
#include "IShape.h"
#include <iostream>
void Layer::Update(const float& deltatime) 
{
	if (m_isVisible == true)
		IComposite::Update(deltatime);
}
void Layer::ProcessInput(const sf::Event& event) 
{
	if (m_isVisible == true)
		IComposite::ProcessInput(event);
}
void Layer::Render()  
{
	if (m_isVisible == true)
	{
		if (m_needsSort == true)
			SortByY();
		for (auto gameObject : m_sortedGameObjects)
		{
			gameObject->Render();
		}
	}
}


void Layer::SetVisible(bool visible)
{
	m_isVisible = visible;
}
bool Layer::IsVisible() const
{
	return m_isVisible;
}

void Layer::SetOpacity(float opacity)
{
	if(opacity>=0.0f && opacity<=1.0f)
		m_opacity = opacity;
}
float Layer::GetOpacity() const
{
	return m_opacity;
}

void Layer::SetZIndex(int zIndex)
{
	m_zIndex = zIndex;
}
int Layer::GetZIndex() const
{
	return m_zIndex;
}

LayersType Layer::GetLayerType() const
{
	return m_type;
}


void Layer::SortByY()
{
	KT::Vector<IComponent*> children_Layer = getChildren();
	m_sortedGameObjects.clear();
	//KT::Vector<IGameObject*> temp_GameObject;
	for (auto child : children_Layer)
	{
		if (auto gameObject = dynamic_cast<IGameObject*>(child))
			m_sortedGameObjects.pushBack(gameObject);
	}
	for (auto* obj : m_sortedGameObjects) 
	{
		std::cout << "Objet: " << typeid(*obj).name() << ", Y-Sort: " << obj->sorting_Y_point() << std::endl;
	}
	std::sort(m_sortedGameObjects.begin(), m_sortedGameObjects.end(),
		[]( const IGameObject* a,const IGameObject* b)-> bool
		{
			return a->sorting_Y_point() < b->sorting_Y_point();
		}
	);

	m_needsSort = false;

}
void Layer::AddGameObject(IGameObject* GameObject)
{
	if (GameObject)
	{
		m_sortedGameObjects.pushBack(GameObject);
		m_needsSort = true;
	}
}
void Layer::RemoveGameObject(IGameObject* GameObject)
{
	if (GameObject)
	{
		auto it = std::find(m_sortedGameObjects.begin(), m_sortedGameObjects.end(), GameObject);
		if (it != m_sortedGameObjects.end())
		{
			m_sortedGameObjects.erase(it);
			m_needsSort = true;
		}
	}
}
KT::Vector<IGameObject*>& Layer::GetListGameObject()
{
	return m_sortedGameObjects;
}
const KT::Vector<IGameObject*>& Layer::GetListGameObject() const
{
	return m_sortedGameObjects;
}

void Layer::setNeedsSort(bool neeedSort)
{
	m_needsSort = neeedSort;
}