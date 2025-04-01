#include <iostream>
#include "Layer.h"
#include "IGameObject.h"


Layer::Layer(LayersType type, const int& zPosition)
	: m_type(type)
	, m_zPosition(zPosition)
	, m_isVisible(true)
	, m_opacity(1.0f)
	, m_needsSort(false)
{
}
Layer::~Layer()
{
	ClearListGameObject();
}


void Layer::Update(const float& deltatime)
{
	if (m_isVisible == true)
	{
		for (auto gameObject : m_GameObjects)
		{
			Reader_GameObjectType reader(gameObject->getGameObjectType());
			if (reader.isVisible() == true)
				gameObject->Update(deltatime);
		}
	}
}
void Layer::ProcessInput(const sf::Event& event)
{
	if (m_isVisible == true)
	{
		for (auto gameObject : m_GameObjects)
		{
			Reader_GameObjectType reader(gameObject->getGameObjectType());
			if (reader.isVisible() == true)
				gameObject->ProcessInput(event);
		}
	}
}
void Layer::Render()
{
	if (m_isVisible == true)
	{
		if (m_needsSort == true)
			SortByY();
		for (auto gameObject : m_GameObjects)
		{
			Reader_GameObjectType reader(gameObject->getGameObjectType());
			if (reader.isVisible() == true)
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
	m_opacity = opacity;
}
float Layer::GetOpacity() const
{
	return m_opacity;
}

void Layer::SetzPosition(int zPosition)
{
	m_zPosition = zPosition;
}
int Layer::GetzPosition() const
{
	return m_zPosition;
}

LayersType Layer::GetLayerType() const
{
	return m_type;
}

void Layer::AddGameObject(IGameObject* GameObject)
{
	if (GameObject == nullptr)
	{
		std::cerr << "Warning: Attempt to add null GameObject to Layer" << std::endl;
		return;
	}
	m_GameObjects.push_back(GameObject);
	GameObject->setParent(this);
	m_needsSort = true;
}
void Layer::RemoveGameObject(IGameObject* GameObject)
{
	if (GameObject == nullptr)
	{
		std::cerr << "Warning: Attempt to remove null GameObject to Layer" << std::endl;
		return;
	}

	auto it = std::find(m_GameObjects.begin(), m_GameObjects.end(), GameObject);
	if (it == m_GameObjects.end())
		throw std::logic_error("You can't delete a GameObject that isn't in the vector");
	else
	{
		m_GameObjects.erase(it);
		GameObject->setParent(nullptr);
		m_needsSort = true;
	}
}
void Layer::ClearListGameObject()
{
	for (auto it = m_GameObjects.rbegin(); it != m_GameObjects.rend(); ++it)
		delete* it;
	m_GameObjects.clear();
	m_needsSort = false;
}
std::vector<IGameObject*>& Layer::GetListGameObject()
{
	return m_GameObjects;
}
const std::vector<IGameObject*>& Layer::GetListGameObject() const
{
	return m_GameObjects;
}

void Layer::setNeedSort(bool needsSort)
{
	m_needsSort = needsSort;
}
void Layer::SortByY()
{

	std::sort(m_GameObjects.begin(), m_GameObjects.end(),
		[]( const IGameObject* a,const IGameObject* b)-> bool
		{
			Reader_GameObjectType readerA(a->getGameObjectType());
			Reader_GameObjectType readerB(b->getGameObjectType());
			if (!readerA.isVisible() || !readerB.isVisible())
				return false; 
			return a->sorting_Y_point() < b->sorting_Y_point();
		}
		);
	m_needsSort = false;
}
