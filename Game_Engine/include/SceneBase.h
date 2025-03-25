#pragma once
#include "Composite.h"
#include "TextureCache.h"
#include "Layer.h"
#include<iostream>

class ISceneBase : public IComposite
{
public:

	ISceneBase(sf::RenderWindow* window, const float& framerate, TextureCache* texture);

	virtual ~ISceneBase();

	virtual void Update(const float& deltatime) = 0;

	virtual void ProcessInput(const sf::Event& event) = 0;

	virtual void Render() = 0;

	void setSceneIdx(int idx);

	int getSceneIdx();

	void AddLayer(Layer* layer);
	void RemoveLayer(Layer* layer);
	void ClearListLayer();

	std::vector<Layer*>& GetListLayer();
	const  std::vector<Layer*>& GetListLayer() const;

	Layer* GetLayerByType(LayersType type);

	sf::Time getRefreshTime();

	sf::RenderWindow* getWindow();

	/*sf::Vector2f getBackgroundCenter();
	sf::Vector2f getBackgroundSize();
	sf::Vector2f getLeftTopCorner();
	sf::Vector2f getRightBotomCorner();
	sf::Vector2f GetCenterWindow();*/
	TextureCache* getTexture() { return m_texture; }



protected:
	//IShapeSFML* m_Background;
	TextureCache* m_texture;
private:
	int m_Sceneidx;
	sf::RenderWindow* m_Window;
	sf::Time m_FefreshTime;
	std::vector<Layer*> m_layer;
	//bool m_needSort;
	
};
