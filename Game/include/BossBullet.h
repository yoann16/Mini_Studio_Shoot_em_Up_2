//#pragma once
//#include "GameObject.h"
//#include "RandomNumber.h"
//
//enum class ProjectileType {
//    Normal,
//    Large,
//    Fast,
//    Explosive,
//    Homing
//};
//
//class EntityProjectileBase : public IBullet
//{
//public:
//    EntityProjectileBase(AnimateSprite animate, IComposite* scene, ITurret* gun, float angle, float speed, float size, float hp);
//    virtual void Update(const float& deltatime) override;
//    virtual void HandleCollision(IGameObject* object) override;
//
//protected:
//    Timer m_animationTimer;
//    virtual void updateAnimation(const float& deltaTime);
//    virtual bool shouldIgnoreCollision(IGameObject* object) const;
//    sf::Vector2f m_absolutePosition;
//    bool m_useAbsolutePosition;
//};
//
//class EntityProjectile : public EntityProjectileBase
//{
//public:
//    EntityProjectile(IComposite* scene, ITurret* gun, float angle, float speed, float size);
//    virtual void Render() override;
//    virtual void ProssesInput(const sf::Event& event) override {};
//};
//
//class LargeProjectile : public EntityProjectileBase
//{
//public:
//    LargeProjectile(IComposite* scene, ITurret* gun, float angle, float speed, float size, float damage);
//    virtual void Render() override;
//    virtual void ProssesInput(const sf::Event& event) override {};
//    virtual void Update(const float& deltatime) override;
//
//protected:
//    virtual bool shouldIgnoreCollision(IGameObject* object) const override;
//    Timer m_lifetimeTimer;
//
//private:
//    float m_damage;
//};
//
//class FastProjectile : public EntityProjectileBase
//{
//public:
//    FastProjectile(AnimateSprite animate, IComposite* scene, ITurret* gun, float angle, float speed, float size, float hp);
//    virtual void Render() override;
//    virtual void ProssesInput(const sf::Event& event) override {};
//
//protected:
//    virtual bool shouldIgnoreCollision(IGameObject* object) const override;
//};
//
//class ShieldProjectile : public DestructibleObject, public ILeaf
//{
//public:
//    ShieldProjectile(IComposite* scene, IShapeSFML* owner, float duration, float radius);
//    virtual void Render() override;
//    virtual void ProssesInput(const sf::Event& event) override {};
//    virtual void Update(const float& deltatime) override;
//    virtual void HandleCollision(IGameObject* object) override;
//
//private:
//    IShapeSFML* m_owner;
//    AnimateSprite m_animate;
//    Timer m_duration;
//    Timer m_pulseTimer;
//    float m_radius;
//    float m_initialRadius;
//    bool m_growing;
//};
//
//using BossBulletBase = EntityProjectileBase;
//using BossBullet = EntityProjectile;
//using GrowingBullet = LargeProjectile;
//using FastBullet = FastProjectile;
//
//enum class BossProjectileType {
//    Normal = static_cast<int>(ProjectileType::Normal),
//    Growing = static_cast<int>(ProjectileType::Large),
//    Fast = static_cast<int>(ProjectileType::Fast)
//};