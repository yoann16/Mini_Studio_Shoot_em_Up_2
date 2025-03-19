#pragma once
#include "IGameObject.h"

enum class LayersType
{
	 Background
	,Middleground
	,Foreground
};

class Layer :public ILeaf
{
public:
	Layer(ISceneBase* scene, LayersType type, int zIndex)
		:ILeaf(scene)
		, m_type(type)
		, m_zIndex(zIndex)
		, m_isVisible(true)
		, m_opacity(1.0f)
		, m_needsSort(false)
		, m_sortedGameObjects()
	{ }
	virtual ~Layer()=default;

	
	void Update(const float& deltatime) override;
	void ProcessInput(const sf::Event& event) override;
	void Render() override;

	
	void SetVisible(bool visible);
	bool IsVisible() const;

	void SetOpacity(float opacity);
	float GetOpacity() const;

	void SetZIndex(int zIndex);
	int GetZIndex() const;

	LayersType GetLayerType() const;

	
	void SortByY();

	void AddGameObject(IGameObject* GameObject);
	void RemoveGameObject(IGameObject* GameObject);
	KT::Vector<IGameObject*>& GetListGameObject();
	const KT::Vector<IGameObject*>& GetListGameObject() const;

	void setNeedsSort(bool neeedSort);
	
private:
	LayersType m_type;
	KT::Vector<IGameObject*> m_sortedGameObjects;
	int m_zIndex;
	bool m_isVisible;
	float m_opacity;
	bool m_needsSort;

};