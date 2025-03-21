#include "Layer.h"
//#include "IShape.h"

Layer::Layer(IComposite* scene, LayersType type, const int& zPosition)
	:IComposite(scene)
	, m_type(type)
	, m_zPosition(zPosition)
	, m_isVisible(true)
	, m_opacity(1.0f)
	, m_needsSort(false)
{
}
Layer::~Layer()
{
	for (auto it = m_GameObjects.rbegin(); it != m_GameObjects.rend(); ++it)
		delete* it;
	m_GameObjects.clear();
}


void Layer::Update(const float& deltatime)
{
	if (m_isVisible == true)
		IComposite::Update(deltatime);
		/*for (auto it = m_GameObjects.begin();it != m_GameObjects.end();++it)
			IComposite::Update(deltatime);*/
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
		for (auto gameObject : m_GameObjects)
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
	if (GameObject!=nullptr)
	{
		
		m_GameObjects.push_back(GameObject);
		m_needsSort = true;
	}
}
void Layer::RemoveGameObject(IGameObject* GameObject)
{
	if (GameObject)
	{
		auto it = std::find(m_GameObjects.begin(), m_GameObjects.end(), GameObject);
		if (it != m_GameObjects.end())
		{
			m_GameObjects.erase(it);
			m_needsSort = true;
		}
	}
}
void Layer::ClearListGameObject()
{
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
					return a->sorting_Y_point() < b->sorting_Y_point();
				}
			);
	m_needsSort = false;
}




















//void Layer::Update(const float& deltatime) 
//{
//	if (m_isVisible == true)
//		ILeaf::Update(deltatime);
//}
//void Layer::ProcessInput(const sf::Event& event) 
//{
//	if (m_isVisible == true)
//		ILeaf::ProcessInput(event);
//}
//void Layer::Render()  
//{
//	if (m_isVisible == true)
//	{
//		if (m_needsSort == true)
//			SortByY();
//		for (auto gameObject : m_sortedGameObjects)
//		{
//			gameObject->Render();
//		}
//	}
//}
//
//
//void Layer::SetVisible(bool visible)
//{
//	m_isVisible = visible;
//}
//bool Layer::IsVisible() const
//{
//	return m_isVisible;
//}
//
//void Layer::SetOpacity(float opacity)
//{
//	if(opacity>=0.0f && opacity<=1.0f)
//		m_opacity = opacity;
//}
//float Layer::GetOpacity() const
//{
//	return m_opacity;
//}
//
//void Layer::SetZIndex(int zIndex)
//{
//	m_zIndex = zIndex;
//}
//int Layer::GetZIndex() const
//{
//	return m_zIndex;
//}
//
//LayersType Layer::GetLayerType() const
//{
//	return m_type;
//}
//
//
//void Layer::SortByY()
//{
//	std::sort(m_sortedGameObjects.begin(), m_sortedGameObjects.end(),
//		[]( const IGameObject* a,const IGameObject* b)-> bool
//		{
//			return a->sorting_Y_point() < b->sorting_Y_point();
//		}
//	);
//
//	m_needsSort = false;
//}
//void Layer::AddGameObject(IGameObject* GameObject)
//{
//	if (GameObject)
//	{
//		m_sortedGameObjects.pushBack(GameObject);
//		m_needsSort = true;
//	}
//}
//void Layer::RemoveGameObject(IGameObject* GameObject)
//{
//	if (GameObject)
//	{
//		auto it = std::find(m_sortedGameObjects.begin(), m_sortedGameObjects.end(), GameObject);
//		if (it != m_sortedGameObjects.end())
//		{
//			m_sortedGameObjects.erase(it);
//			m_needsSort = true;
//		}
//	}
//}
//KT::Vector<IGameObject*>& Layer::GetListGameObject()
//{
//	return m_sortedGameObjects;
//}
//const KT::Vector<IGameObject*>& Layer::GetListGameObject() const
//{
//	return m_sortedGameObjects;
//}
//
//void Layer::setNeedSort(bool needsSort)
//{
//	m_needsSort = needsSort;
//}