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

	IComposite(IComposite* parent = nullptr);
	~IComposite();

	std::vector<IComponent*> getChildren();
	const std::vector<IComponent*> getChildren() const;

private:
	void add(IComponent* data);
	void remove(IComponent* data);
	std::vector<IComponent*> m_children;
};

class ILeaf : public IComponent
{
public:
	ILeaf(IComposite* parent);
	virtual ~ILeaf() = default;
};


class Root : public IComposite
{
public:
	Root();
};
