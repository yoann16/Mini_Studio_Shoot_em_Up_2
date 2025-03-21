#include "SceneBase.h"
#include "IGameObject.h"
#include"IShape.h"

ISceneBase::ISceneBase(sf::RenderWindow* window, const float& framerate, TextureCache* texture) 
	:RootScene(this)
	,m_Window(window)
	, m_FefreshTime(sf::seconds(1.f /framerate))
	, m_Sceneidx(0)
	,m_Background(nullptr)
	, m_texture(texture)
{
}

ISceneBase::~ISceneBase()
{
	delete m_Background;
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

sf::Vector2f ISceneBase::getBackgroundCenter()
{
	return m_Background->getPosition();
}

sf::Vector2f ISceneBase::getBackgroundSize()
{
	return m_Background->getSize();
}

sf::Vector2f ISceneBase::getLeftTopCorner()
{
	sf::Vector2f result;
	result.x =( m_Background->getPosition().x -( m_Background->getSize().x / 2));
	result.y = (m_Background->getPosition().y -( m_Background->getSize().y / 2));
	return result;
}

sf::Vector2f ISceneBase::getRightBotomCorner()
{
	sf::Vector2f result;
	result.x = (m_Background->getPosition().x + (m_Background->getSize().x / 2));
	result.y = (m_Background->getPosition().y + (m_Background->getSize().y / 2));
	return result;
}

sf::Vector2f ISceneBase::GetCenterWindow()
{
	sf::Vector2f centreFenetre = getWindow()->getView().getCenter();
	sf::Vector2f centreBackground = m_Background->getPosition();
	sf::Vector2f positionRelative = centreFenetre - centreBackground;
	return positionRelative;
}