#pragma once


class ISceneBase;
class IGameObject;
class Reader_GameObjectType;

#include <vector>
#include <SFML/Graphics.hpp>
#include "Composite.h"

enum class LayersType
{
	 Background
	,Middleground
	,Foreground
};



class Layer :public IComposite
{
public:
	Layer(LayersType type, const int& zPosition);
	virtual ~Layer();

	
	void Update(const float& deltatime);
	void ProcessInput(const sf::Event& event);
	void Render();


	
	void SetVisible(bool visible);
	bool IsVisible() const;

	void SetOpacity(float opacity);
	float GetOpacity() const;

	void SetzPosition(int zPosition);
	int GetzPosition() const;

	LayersType GetLayerType() const;

	void AddGameObject(IGameObject* GameObject);
	void RemoveGameObject(IGameObject* GameObject);
	void ClearListGameObject();
	std::vector<IGameObject*>& GetListGameObject();
	const std::vector<IGameObject*>& GetListGameObject() const;

	void setNeedSort(bool needsSort);
	void SortByY();
	
private:
	LayersType m_type;
	int m_zPosition;
	bool m_isVisible;
	float m_opacity;
	bool m_needsSort;
	std::vector<IGameObject*> m_GameObjects;
};