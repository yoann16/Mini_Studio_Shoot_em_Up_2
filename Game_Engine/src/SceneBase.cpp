#include "SceneBase.h"

ISceneBase::ISceneBase(sf::RenderWindow* window, const float& framerate, TextureCache* texture) 
	:IComposite(nullptr)
	,m_Window(window)
	,m_FefreshTime(sf::seconds(1.f /framerate))
	,m_Sceneidx(0)
	,m_texture(texture)
	,m_layer()
{
}

void ISceneBase::setSceneIdx(int idx)
{
	m_Sceneidx = idx;
}

int ISceneBase::getSceneIdx()
{
	return m_Sceneidx;
}

sf::Time ISceneBase::getRefreshTime()
{
	return m_FefreshTime;
}

sf::RenderWindow* ISceneBase::getWindow()
{
	return m_Window;
}

void ISceneBase::AddLayer(Layer* layer)
{
	if (layer == nullptr)
	{
		std::cerr << "Warning: Attempt to add null Layer to Scene" << std::endl;
		return;
	}

	auto it = std::find(m_layer.begin(), m_layer.end(), layer);
	if (it != m_layer.end())
		throw std::logic_error("You cannot add 2x the same Layer in the vector");

	m_layer.push_back(layer);
	layer->setParent(this);

	/*TODO Changer le tri pour utiliser un tri plus générique
	pour les GameObject et les Layer(tri trop puissant pour 2-3 Layer)*/
	std::sort(m_layer.begin(), m_layer.end(),
		[](const Layer* a, const Layer* b)-> bool
		{
			return a->GetzPosition() < b->GetzPosition();
		}
	);
}
void ISceneBase::RemoveLayer(Layer* layer)
{
	if (layer == nullptr)
	{
		std::cerr << "Warning: Attempt to remove null Layer to Scene" << std::endl;
		return;
	}

	auto it = std::find(m_layer.begin(), m_layer.end(), layer);
	if (it == m_layer.end())
		throw std::logic_error("You can't delete a Layer that isn't in the vector");
	else
	{
		m_layer.erase(it);
		layer->setParent(nullptr);
	}

	/*TODO Changer le tri pour utiliser un tri plus générique
	pour les GameObject et les Layer(tri trop puissant pour 2-3 Layer)*/
	std::sort(m_layer.begin(), m_layer.end(),
		[](const Layer* a, const Layer* b)-> bool
		{
			return a->GetzPosition() < b->GetzPosition();
		}
	);
}
void ISceneBase::ClearListLayer()
{
	for (auto it = m_layer.rbegin(); it != m_layer.rend(); ++it)
		delete* it;
	m_layer.clear();
}
std::vector<Layer*>& ISceneBase::GetListLayer()
{
	return m_layer;
}
const  std::vector<Layer*>& ISceneBase::GetListLayer() const
{
	return m_layer;
}
Layer* ISceneBase::GetLayerByType(LayersType type)
{
	for (auto it = m_layer.begin(); it != m_layer.end(); ++it)
	{
		if ((*it)->GetLayerType() == type)
			return (*it);
	}
	return nullptr;
}
