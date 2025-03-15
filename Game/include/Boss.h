//#pragma once
//#include "IGameObject.h"
//#include "GameObject.h"
//#include "BehaviorTree.h"
//#include "BossBullet.h"
//
//namespace BossAI {
//    class RandomAttackSelector;
//    class RandomMovementSelector;
//}
//
//enum class EntityMovementPattern {
//    Horizontal,
//    Vertical,
//    Diagonal,
//    Random,
//    Chase,
//    Stationary
//};
//
//enum class EntityPhase
//{
//	One,
//	Two,
//	Three,
//	Four,
//	Five
//};
//
//struct EntityParameters {
//    float speed;
//    float attackRate;
//    int attackCount;
//    float spreadAngle;
//    float projectileSize;
//    float projectileSpeed;
//    float damageMultiplier;
//
//    static EntityParameters getForPhase(EntityPhase phase);
//};
//
//class Boss : public DestructibleObject, public IComposite
//{
//public:
//    Boss(IComposite* scene, const sf::Vector2f& spawnPosition, float maxHealth = 5000.0f);
//    virtual ~Boss();
//
//    void ProssesInput(const sf::Event& event) override {};
//    void Update(const float& deltatime) override;
//    void Render() override;
//    void HandleCollision(IGameObject* object) override;
//    void ChangeLife(const float& life) override;
//
//    float getMaxLife() const { return m_maxLife; }
//    float getCurrentLife() const { return m_life; }
//    IComposite* getScene() const { return m_scene; }
//
//    void setSpeed(float speed);
//    void moveTowards(const sf::Vector2f& target, float deltaTime);
//    void moveToPosition(const sf::Vector2f& position);
//
//    virtual void fireProjectiles(int count, float spreadAngle);
//    virtual void fireSpecialProjectile(ProjectileType type);
//
//    void fireGrowingProjectile();
//    void fireFastProjectile();
//
//    virtual void activateDefensiveAbility(float duration);
//    virtual void activateOffensiveBoost(float multiplier, float duration);
//    virtual void regenerateHealth(float amount);
//
//    virtual void updateEntityParameters();
//    EntityPhase getCurrentPhase() const { return m_currentPhase; }
//
//protected:
//    virtual void setupBehaviorTree();
//    virtual void findTarget();
//    virtual void createWeapons(float offset);
//    sf::Vector2f worldToScreenPosition(const sf::Vector2f& worldPos) const;
//    sf::Vector2f screenToWorldPosition(const sf::Vector2f& screenPos) const;
//
//    float m_maxLife;
//    float m_speed;
//    BT::RootNode* m_behaviorTree;
//
//    AnimateSprite m_animate;
//    Timer m_animationTimer;
//
//    EntityParameters m_entityParams;
//
//    bool m_offensiveBoostActive;
//    float m_damageMultiplier;
//    Timer m_offensiveBoostTimer;
//    float m_patrolTimer;
//    Timer m_invulnerabilityTimer;
//    bool m_isInvulnerable;
//
//    EntityPhase m_currentPhase;
//
//    IShapeSFML* m_target;
//
//    KT::Array<ITurret*, 4> m_weapons;
//
//    BossAI::RandomAttackSelector* m_specialAttackSelector;
//    BossAI::RandomMovementSelector* m_movementSelector;
//
//    sf::Vector2f m_worldPosition;
//    float m_movementAngle;
//
//    float m_detectionRadius;
//    bool m_isTrackingTarget;
//
//    Timer m_attackTimer;
//
//    float calculateAngleToTarget() const;
//    bool isTargetInDetectionZone() const;
//    bool shouldAttackTarget() const;
//    bool isTargetValid() const;
//};