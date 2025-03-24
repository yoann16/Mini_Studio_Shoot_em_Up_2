#pragma once
#include <SFML/Graphics.hpp>

class Root;
class IComposite;



class IComponent
{
public:
	IComponent(IComposite* parent = nullptr);
	virtual ~IComponent();
	IComponent* getParent();
	const IComponent* getParent() const;

	/*virtual void Update(const float& deltatime) = 0;
	virtual void ProcessInput(const sf::Event& event) = 0;
	virtual void Render() = 0;*/
	/*virtual Component GetComponentType() = 0;
	virtual const Component GetComponentType() const = 0;*/
	Root* getRoot();
	const Root* getRoot() const;

	void setParent(IComposite* parent);
protected:

	IComposite* m_parent;
};


class IComposite : public IComponent
{
public:
	friend IComponent;

	IComposite(IComposite* parent);
	~IComposite();

	/*void Update(const float& deltatime)override;
	void ProcessInput(const sf::Event& event)override;
	void Render()override;*/
	std::vector<IComponent*> getChildren();
	const std::vector<IComponent*> getChildren() const;
	//std::vector<IComponent*> getFullTree();
protected:

	//KT::Vector<IComponant*> IterateAllComposite();
	//const KT::Vector<IComponant*> IterateAllComposite() const;

	/*Component GetComponentType() override
	{
		return Component::IComposite;
	}
	const Component GetComponentType() const override
	{
		return Component::IComposite;
	}*/
private:
	void add(IComponent* data);
	void remove(IComponent* data);
	//void AddFullTree(std::vector<IComponent*>& toAdd, std::vector<IComponent*> iterate);
	std::vector<IComponent*> m_children;
};

class ILeaf : public IComponent
{
public:
	ILeaf(IComposite* parent);
	virtual ~ILeaf() = default;

	/*virtual void Update(const float& deltatime) = 0;
	virtual void ProcessInput(const sf::Event& event) = 0;
	virtual void Render() = 0;*/

	/*Component GetComponentType() override
	{
		return Component::ILeaf;
	}
	const Component GetComponentType() const override
	{
		return Component::ILeaf;
	}*/
};


class Root : public IComposite
{
public:
	Root();
};


