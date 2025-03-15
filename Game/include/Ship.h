//#pragma once
//#include "IGameObject.h"
//#include "GameObject.h"
//
//class Ship : public DestructibleObject, public IComposite
//{
//public:
//	friend BorderShip;
//	Ship(IComposite* scene, IShapeSFML* background);
//	~Ship();
//
//	void ProssesInput(const sf::Event& event) override;
//
//	void physics();
//
//	void Update(const float& deltatime) override;
//	void Render() override;
//
//	float anglecalcul();
//	void HandleCollision(IGameObject* object) override;
//	void ChangeLife(const float& life) override
//	{
//		if (!m_invisibility.ActionIsReady())
//			return;
//
//		m_life += life;
//		if (m_life <= 0)
//			destroy();
//		m_invisibility.resetTimer();
//	}
//
//private:
//	IShapeSFML* m_background;
//	float m_angle;
//	Timer m_elapsedTime;
//	Timer m_invisibility;
//
//	AnimateSprite m_animate;
//	IPhysics* m_physics;
//	KT::Array<ITurret*,2> m_turrets;
//	KT::VectorND<bool, 4> m_strafe{ false,false,false,false };
//};