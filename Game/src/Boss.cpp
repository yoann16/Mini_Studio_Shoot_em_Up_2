//#include "Boss.h"
//#include "RandomNumber.h"
//#include "BossBehavior.h"
//#include "Ship.h"
//#include <functional>
//
//EntityParameters EntityParameters::getForPhase(EntityPhase phase) {
//    EntityParameters params;
//
//    switch (phase) {
//    case EntityPhase::One:
//        params = { 350.0f, 2.0f, 1, 0.0f, 20.0f, 500.0f, 1.0f };
//        break;
//    case EntityPhase::Two:
//        params = { 450.0f, 1.8f, 2, 0.0f, 20.0f, 600.0f, 1.0f };
//        break;
//    case EntityPhase::Three:
//        params = { 550.0f, 1.5f, 3, 0.0f, 25.0f, 700.0f, 1.0f };
//        break;
//    case EntityPhase::Four:
//        params = { 650.0f, 1.2f, 4, 0.0f, 30.0f, 800.0f, 1.0f };
//        break;
//    case EntityPhase::Five:
//        params = { 750.0f, 0.9f, 5, 0.0f, 35.0f, 900.0f, 1.2f };
//        break;
//    }
//
//    return params;
//}
//
//Boss::Boss(IComposite* scene, const sf::Vector2f& spawnPosition, float maxHealth)
//    : DestructibleObject(scene, maxHealth)
//    , IComposite(scene)
//    , m_maxLife(maxHealth)
//    , m_speed(100.0f)
//    , m_behaviorTree(nullptr)
//    , m_animate({ "Boss1.png", "Boss2.png" })
//    , m_animationTimer(0.3)
//    , m_offensiveBoostActive(false)
//    , m_damageMultiplier(1.0f)
//    , m_offensiveBoostTimer(0.0f)
//    , m_invulnerabilityTimer(3.0f)
//    , m_isInvulnerable(false)
//    , m_currentPhase(EntityPhase::One)
//    , m_target(nullptr)
//    , m_specialAttackSelector(nullptr)
//    , m_worldPosition(spawnPosition)
//    , m_movementAngle(0.0f)
//    , m_detectionRadius(1200.0f)
//    , m_isTrackingTarget(false)
//    , m_attackTimer(2.0f)
//    , m_patrolTimer(0.0f)
//{
//    m_entityParams = EntityParameters::getForPhase(m_currentPhase);
//
//    sf::Vector2f screenPosition = worldToScreenPosition(m_worldPosition);
//    m_shape = new RectangleSFML(200.0f, 200.0f, screenPosition);
//    m_shape->setTexture(m_scene->getRoot()->getScene()->getTexture()->getTexture(m_animate.getCurrentPath()));
//
//    findTarget();
//
//    if (!m_target) {
//        IShapeSFML* defaultTarget = new SquareSFML(1, m_scene->getRoot()->getScene()->GetCenterWindow());
//        m_target = defaultTarget;
//    }
//
//    createWeapons(70.0f);
//
//    new Life(this, this, Color::Pink);
//
//    setupBehaviorTree();
//}
//
//Boss::~Boss()
//{
//    delete m_behaviorTree;
//}
//
//void Boss::createWeapons(float weaponOffset) {
//    auto weapon1 = new FixTurret(this, getShape(), sf::Vector2f(-weaponOffset/3, -weaponOffset/3), 0);
//    auto weapon2 = new FixTurret(this, getShape(), sf::Vector2f(weaponOffset/2, -weaponOffset/2), 0);
//    auto weapon3 = new FixTurret(this, getShape(), sf::Vector2f(-weaponOffset/3, weaponOffset/3), 0);
//    auto weapon4 = new FixTurret(this, getShape(), sf::Vector2f(weaponOffset/2, weaponOffset/2), 0);
//
//    m_weapons = { weapon1, weapon2, weapon3, weapon4 };
//
//    for (auto& weapon : m_weapons) {
//        weapon->SetFireRate(m_entityParams.attackRate);
//        weapon->SetOverloadGun(5.0f, 5);
//        weapon->setBullet(m_entityParams.projectileSize, m_entityParams.projectileSpeed, m_damageMultiplier);
//    }
//}
//
//sf::Vector2f Boss::worldToScreenPosition(const sf::Vector2f& worldPos) const {
//    return sf::Vector2f(
//        m_scene->getRoot()->getScene()->getBackgroundCenter().x + worldPos.x,
//        m_scene->getRoot()->getScene()->getBackgroundCenter().y + worldPos.y
//    );
//}
//
//sf::Vector2f Boss::screenToWorldPosition(const sf::Vector2f& screenPos) const {
//    return sf::Vector2f(
//        screenPos.x - m_scene->getRoot()->getScene()->getBackgroundCenter().x,
//        screenPos.y - m_scene->getRoot()->getScene()->getBackgroundCenter().y
//    );
//}
//
//float Boss::calculateAngleToTarget() const
//{
//    if (!m_target) return m_movementAngle;
//
//    try {
//        sf::Vector2f targetWorldPos = screenToWorldPosition(m_target->getPosition());
//
//        float xCorrection = 50.0f * static_cast<float>(m_currentPhase) / 3.0f;
//        targetWorldPos.x += xCorrection;
//
//        sf::Vector2f direction = targetWorldPos - m_worldPosition;
//        return atan2(direction.y, direction.x) * 180.0f / 3.14159f;
//    }
//    catch (...) {
//        return m_movementAngle;
//    }
//}
//
//bool Boss::isTargetValid() const
//{
//    if (!m_target) return false;
//
//    try {
//        sf::Vector2f pos = m_target->getPosition();
//
//        if (std::isnan(pos.x) || std::isnan(pos.y) ||
//            std::isinf(pos.x) || std::isinf(pos.y)) {
//            return false;
//        }
//
//        return true;
//    }
//    catch (...) {
//        return false;
//    }
//}
//
//bool Boss::isTargetInDetectionZone() const
//{
//    if (!m_target) return false;
//
//    try {
//        sf::Vector2f targetWorldPos = screenToWorldPosition(m_target->getPosition());
//        sf::Vector2f diff = targetWorldPos - m_worldPosition;
//        float distanceSquared = diff.x * diff.x + diff.y * diff.y;
//        return distanceSquared <= m_detectionRadius * m_detectionRadius;
//    }
//    catch (...) {
//        return false;
//    }
//}
//
//bool Boss::shouldAttackTarget() const
//{
//    return m_target && isTargetInDetectionZone() && const_cast<Timer&>(m_attackTimer).ActionIsReady();
//}
//
//void Boss::moveToPosition(const sf::Vector2f& position)
//{
//    sf::Vector2f direction = position - m_worldPosition;
//    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
//
//    if (distance > 5.0f) {
//        direction /= distance;
//        m_movementAngle = atan2(direction.y, direction.x) * 180.0f / 3.14159f;
//
//        float deltaTime = 1.0f / 60.0f;
//        sf::Vector2f movement = direction * m_speed * deltaTime;
//        m_worldPosition += movement;
//
//        if (m_isTrackingTarget && m_target) {
//            float targetAngle = calculateAngleToTarget();
//            m_shape->setRotation(targetAngle);
//        }
//        else if (m_target) {
//            sf::Vector2f targetWorldPos = screenToWorldPosition(m_target->getPosition());
//            sf::Vector2f targetDir = targetWorldPos - m_worldPosition;
//            float targetAngle = atan2(targetDir.y, targetDir.x) * 180.0f / 3.14159f;
//
//            float blendedAngle = m_movementAngle * 0.7f + targetAngle * 0.3f;
//            m_shape->setRotation(blendedAngle);
//        }
//        else {
//            m_shape->setRotation(m_movementAngle);
//        }
//    }
//    else if (m_isTrackingTarget && m_target) {
//        float targetAngle = calculateAngleToTarget();
//        m_shape->setRotation(targetAngle);
//    }
//}
//
//void Boss::Update(const float& deltatime)
//{
//    static Timer targetSearchTimer(2.0f);
//
//    if (!m_target || targetSearchTimer.AutoActionIsReady(deltatime)) {
//        findTarget();
//    }
//
//    if (m_isInvulnerable) {
//        m_invulnerabilityTimer.NextTIck(deltatime);
//        if (m_invulnerabilityTimer.ActionIsReady()) {
//            m_isInvulnerable = false;
//        }
//    }
//
//    if (m_animationTimer.AutoActionIsReady(m_scene->getRoot()->getScene()->getRefreshTime().asSeconds())) {
//        m_animate.ChangeToNextPath();
//        m_shape->setTexture(m_scene->getRoot()->getScene()->getTexture()->getTexture(m_animate.getCurrentPath()));
//    }
//
//    m_attackTimer.NextTIck(deltatime);
//
//    m_isTrackingTarget = m_target && isTargetInDetectionZone();
//
//    if (m_isTrackingTarget && m_target) {
//        float angleToTarget = calculateAngleToTarget();
//        m_shape->setRotation(angleToTarget);
//
//        if (m_attackTimer.ActionIsReady()) {
//            fireProjectiles(m_entityParams.attackCount, m_entityParams.spreadAngle);
//            m_attackTimer.setNewTimer(m_entityParams.attackRate);
//        }
//    }
//    else {
//        m_patrolTimer += deltatime;
//
//        float radius = 200.0f;
//        sf::Vector2f patrolPos;
//        patrolPos.x = sin(m_patrolTimer * 0.5f) * radius;
//        patrolPos.y = cos(m_patrolTimer * 0.25f) * radius;
//        moveToPosition(patrolPos);
//    }
//
//    if (m_offensiveBoostActive) {
//        m_offensiveBoostTimer.NextTIck(deltatime);
//        if (m_offensiveBoostTimer.ActionIsReady()) {
//            m_offensiveBoostActive = false;
//            m_damageMultiplier = 1.0f;
//
//            for (auto& weapon : m_weapons) {
//                weapon->setBullet(m_entityParams.projectileSize, m_entityParams.projectileSpeed, 1.0f);
//            }
//        }
//    }
//
//    m_shape->setPosition(worldToScreenPosition(m_worldPosition));
//
//    if (m_behaviorTree) {
//        m_behaviorTree->tick();
//    }
//
//    IComposite::Update(deltatime);
//}
//
//void Boss::Render()
//{
//    m_scene->getRoot()->getScene()->getWindow()->draw(static_cast<RectangleSFML*>(m_shape)->getShape());
//    IComposite::Render();
//}
//
//void Boss::HandleCollision(IGameObject* object)
//{
//    if (object->globalGameObjectType() != GameObjectType::DestructibleObject)
//        return;
//
//    IBullet* bullet = getObj<IBullet*>(object);
//    if (bullet) {
//        for (auto& weapon : m_weapons) {
//            if (bullet->getTurret() == weapon) {
//                return;
//            }
//        }
//    }
//
//    if (m_isInvulnerable)
//        return;
//
//    ChangeLife(-1.0f);
//
//    m_isInvulnerable = true;
//    m_invulnerabilityTimer.setNewTimer(1.0f);
//    m_invulnerabilityTimer.resetTimer();
//
//}
//
//void Boss::ChangeLife(const float& life)
//{
//    if (life < 0 && m_isInvulnerable)
//        return;
//
//    DestructibleObject::ChangeLife(life);
//
//    float healthPercentage = getCurrentLife() / m_maxLife;
//    EntityPhase newPhase;
//
//    if (healthPercentage <= 0.2f) newPhase = EntityPhase::Five;
//    else if (healthPercentage <= 0.4f) newPhase = EntityPhase::Four;
//    else if (healthPercentage <= 0.6f) newPhase = EntityPhase::Three;
//    else if (healthPercentage <= 0.8f) newPhase = EntityPhase::Two;
//    else newPhase = EntityPhase::One;
//
//    if (newPhase != m_currentPhase) {
//        m_currentPhase = newPhase;
//        updateEntityParameters();
//    }
//}
//
//void Boss::setSpeed(float speed)
//{
//    m_speed = speed;
//}
//
//void Boss::moveTowards(const sf::Vector2f& target, float deltaTime)
//{
//    sf::Vector2f targetWorldPos = screenToWorldPosition(target);
//
//    sf::Vector2f direction = targetWorldPos - m_worldPosition;
//    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//
//    if (length > 0) {
//        direction /= length;
//    }
//
//    sf::Vector2f movement = direction * m_speed * deltaTime;
//    m_worldPosition += movement;
//
//    if (length > 0) {
//        float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f;
//        m_shape->setRotation(angle);
//    }
//}
//
//void Boss::fireProjectiles(int count, float spreadAngle)
//{
//    if (!m_target || !m_isTrackingTarget) return;
//
//    float targetingAngle;
//    try {
//        targetingAngle = calculateAngleToTarget();
//    }
//    catch (...) {
//        targetingAngle = m_shape->getangle();
//    }
//
//    for (auto& weapon : m_weapons) {
//        weapon->SetOverloadGun(0.1f, count);
//        weapon->setBullet(
//            m_entityParams.projectileSize,
//            m_entityParams.projectileSpeed,
//            m_damageMultiplier
//        );
//
//        weapon->getShape()->setRotation(targetingAngle);
//
//        if (count == 1) {
//            weapon->Fire();
//        }
//        else {
//            float totalSpread = spreadAngle;
//            float angleStep = totalSpread / (count - 1);
//            float startAngle = targetingAngle - totalSpread / 2.0f;
//
//            for (int i = 0; i < count; ++i) {
//                float bulletAngle = startAngle + i * angleStep;
//                weapon->getShape()->setRotation(bulletAngle);
//                weapon->Fire();
//            }
//
//            weapon->getShape()->setRotation(targetingAngle);
//        }
//    }
//}
//
//void Boss::fireSpecialProjectile(ProjectileType type)
//{
//    switch (type) {
//    case ProjectileType::Large:
//    {
//        int firstWeapon = UseRandomNumber().getRandomNumber<int>(0, 3);
//        int secondWeapon = (firstWeapon + 2) % 4;
//
//        float angleToTarget = m_target ? calculateAngleToTarget() : m_shape->getangle();
//
//        new LargeProjectile(
//            m_scene,
//            m_weapons[firstWeapon],
//            angleToTarget,
//            450.0f,
//            60.0f,
//            3.0f
//        );
//
//        new LargeProjectile(
//            m_scene,
//            m_weapons[secondWeapon],
//            angleToTarget,
//            450.0f,
//            60.0f,
//            3.0f
//        );
//
//    }
//    break;
//
//    case ProjectileType::Fast:
//    {
//        AnimateSprite fastProjectileSprite({ "FastBullet.png", "FastBullet2.png" });
//        for (auto& weapon : m_weapons) {
//            new FastProjectile(
//                fastProjectileSprite,
//                m_scene,
//                weapon,
//                weapon->getShape()->getangle(),
//                1200.0f,
//                10.0f,
//                1.0f
//            );
//        }
//    }
//    break;
//    }
//}
//
//void Boss::activateDefensiveAbility(float duration)
//{
//    regenerateHealth(25.0f);
//}
//
//void Boss::activateOffensiveBoost(float multiplier, float duration)
//{
//    m_offensiveBoostActive = true;
//    m_damageMultiplier = multiplier;
//    m_offensiveBoostTimer.setNewTimer(duration);
//
//    for (auto& weapon : m_weapons) {
//        weapon->setBullet(m_entityParams.projectileSize, m_entityParams.projectileSpeed, m_damageMultiplier);
//    }
//}
//
//void Boss::regenerateHealth(float amount)
//{
//    float newHealth = m_life + amount;
//    if (newHealth > m_maxLife) {
//        newHealth = m_maxLife;
//    }
//    m_life = newHealth;
//}
//
//void Boss::updateEntityParameters()
//{
//    m_entityParams = EntityParameters::getForPhase(m_currentPhase);
//    m_speed = m_entityParams.speed;
//
//    m_attackTimer.setNewTimer(m_entityParams.attackRate);
//
//    for (auto& weapon : m_weapons) {
//        weapon->SetFireRate(m_entityParams.attackRate);
//        weapon->setBullet(m_entityParams.projectileSize, m_entityParams.projectileSpeed, m_damageMultiplier);
//    }
//}
//
//void Boss::findTarget()
//{
//    auto root = m_scene->getRoot();
//    m_target = nullptr;
//
//    std::function<bool(IComposite*)> findShipInChildren = [&](IComposite* node) -> bool {
//        if (!node) return false;
//
//        for (auto& child : node->getChildren()) {
//            if (!child) continue;
//
//            Ship* ship = getObj<Ship*>(child);
//            if (ship) {
//                m_target = ship->getShape();
//                return true;
//            }
//
//            if (auto composite = dynamic_cast<IComposite*>(child)) {
//                if (findShipInChildren(composite)) return true;
//            }
//        }
//        return false;
//        };
//
//    for (auto& node : root->getChildren()) {
//        if (!node) continue;
//
//        Ship* ship = getObj<Ship*>(node);
//        if (ship) {
//            m_target = ship->getShape();
//            return;
//        }
//    }
//
//    findShipInChildren(root);
//}
//
//void Boss::fireGrowingProjectile()
//{
//    fireSpecialProjectile(ProjectileType::Large);
//}
//
//void Boss::fireFastProjectile()
//{
//    fireSpecialProjectile(ProjectileType::Fast);
//}
//
//void Boss::setupBehaviorTree()
//{
//    m_behaviorTree = new BT::RootNode(this);
//
//    BT::Sequence* mainSequence = new BT::Sequence(m_behaviorTree);
//
//    BossAI::MovementPatternTimerNode* movementPatternTimer = new BossAI::MovementPatternTimerNode(mainSequence, 30.0f);
//    BT::DoNTime* selectNewPattern = new BT::DoNTime(movementPatternTimer, 1);
//
//    class SelectRandomPatternNode : public BossAI::BossBehaviorNode<BT::IActionNode>
//    {
//    public:
//        SelectRandomPatternNode(BT::ICompositeNode* parent, BossAI::RandomMovementSelector* selector)
//            : BossAI::BossBehaviorNode<BT::IActionNode>(parent), m_selector(selector) {}
//
//        BT::Status tick() override {
//            int randomPattern = UseRandomNumber().getRandomNumber<int>(0, 2);
//            m_selector->setCurrentPattern(static_cast<BossMovementPattern>(randomPattern));
//            return BT::Success;
//        }
//
//        void display() override {
//        }
//
//    private:
//        BossAI::RandomMovementSelector* m_selector;
//    };
//
//    m_movementSelector = new BossAI::RandomMovementSelector(mainSequence);
//    new BossAI::HorizontalPatternNode(m_movementSelector);
//    new BossAI::VerticalPatternNode(m_movementSelector);
//    new BossAI::DiagonalPatternNode(m_movementSelector);
//    new SelectRandomPatternNode(selectNewPattern, m_movementSelector);
//
//    class AlwaysTrueNode : public BossAI::BossBehaviorNode<BT::IConditionalNode>
//    {
//    public:
//        AlwaysTrueNode(BT::ICompositeNode* parent)
//            : BossAI::BossBehaviorNode<BT::IConditionalNode>(parent) {}
//
//        bool condition() override {
//            return true;
//        }
//    };
//
//    BT::IConditionalNode* specialAttackCondition = new AlwaysTrueNode(mainSequence);
//    BT::Sequence* specialAttackSequence = new BT::Sequence(specialAttackCondition);
//
//    class ForceSpecialAttackTimerNode : public BossAI::BossBehaviorNode<BT::IActionNode>
//    {
//    public:
//        ForceSpecialAttackTimerNode(BT::ICompositeNode* parent, float minInterval, float maxInterval)
//            : BossAI::BossBehaviorNode<BT::IActionNode>(parent),
//            m_timer(0.0f),
//            m_minInterval(minInterval),
//            m_maxInterval(maxInterval),
//            m_initialized(false) {
//        }
//        BT::Status tick() override {
//            if (!m_initialized) {
//                int nextInterval = UseRandomNumber().getRandomNumber<int>(m_minInterval, m_maxInterval);
//                m_timer.setNewTimer(nextInterval);
//                m_initialized = true;
//            }
//
//            m_timer.NextTIck(1.0f / 60.0f);
//
//            if (m_timer.ActionIsReady()) {
//                int attackType = UseRandomNumber().getRandomNumber<int>(0, 3);
//
//                if (attackType == 3) attackType = 4;
//
//                switch (attackType) {
//                case 0:
//                    getGameObject()->regenerateHealth(50.0f);
//                    break;
//                case 1:
//                    getGameObject()->fireGrowingProjectile();
//                    break;
//                case 2:
//                    getGameObject()->fireFastProjectile();
//                    break;
//                case 4:
//                    getGameObject()->activateOffensiveBoost(2.0f, 8.0f);
//                    break;
//                }
//
//                m_initialized = false;
//            }
//
//            return BT::Success;
//        }
//
//    private:
//        Timer m_timer;
//        float m_minInterval;
//        float m_maxInterval;
//        bool m_initialized;
//    };
//
//    new ForceSpecialAttackTimerNode(specialAttackSequence, 5.0f, 15.0f);
//
//    BT::IConditionalNode* phaseAttackCondition = new AlwaysTrueNode(mainSequence);
//    BT::Sequence* phaseAttackSequence = new BT::Sequence(phaseAttackCondition);
//
//    class PhaseBasedAttacks : public BossAI::BossBehaviorNode<BT::IActionNode>
//    {
//    public:
//        PhaseBasedAttacks(BT::ICompositeNode* parent)
//            : BossAI::BossBehaviorNode<BT::IActionNode>(parent),
//            m_phase(1),
//            m_timer(1.2f),
//            m_initialized(false)
//        {
//        }
//
//        BT::Status tick() override {
//            if (!m_initialized) {
//                m_timer.setNewTimer(1.2f);
//                m_initialized = true;
//            }
//
//            float healthPercent = (getGameObject()->getCurrentLife() / getGameObject()->getMaxLife()) * 100.0f;
//            int currentPhase = 1;
//
//            if (healthPercent <= 20.0f) currentPhase = 5;
//            else if (healthPercent <= 40.0f) currentPhase = 4;
//            else if (healthPercent <= 60.0f) currentPhase = 3;
//            else if (healthPercent <= 80.0f) currentPhase = 2;
//
//            if (currentPhase != m_phase) {
//                m_phase = currentPhase;
//
//                updatePhaseParameters();
//
//                m_timer.resetTimer();
//
//                getGameObject()->updateEntityParameters();
//            }
//
//            m_timer.NextTIck(1.0f / 60.0f);
//
//            if (m_timer.ActionIsReady()) {
//                int bulletCount;
//                float spreadAngle;
//
//                switch (m_phase) {
//                case 1:
//                    bulletCount = 1;
//                    spreadAngle = 0.0f;
//                    m_timer.setNewTimer(1.2f);
//                    break;
//                case 2:
//                    bulletCount = 2;
//                    spreadAngle = 15.0f;
//                    m_timer.setNewTimer(1.0f);
//                    break;
//                case 3:
//                    bulletCount = 3;
//                    spreadAngle = 30.0f;
//                    m_timer.setNewTimer(0.8f);
//                    break;
//                case 4:
//                    bulletCount = 4;
//                    spreadAngle = 45.0f;
//                    m_timer.setNewTimer(0.6f);
//                    break;
//                case 5:
//                    bulletCount = 5;
//                    spreadAngle = 60.0f;
//                    m_timer.setNewTimer(0.4f);
//                    break;
//                }
//
//                getGameObject()->fireProjectiles(bulletCount, spreadAngle);
//            }
//
//            return BT::Success;
//        }
//
//    private:
//        int m_phase;
//        Timer m_timer;
//        bool m_initialized;
//
//        void updatePhaseParameters() {
//            switch (m_phase) {
//            case 1:
//                m_timer.setNewTimer(1.2f);
//                break;
//            case 2:
//                m_timer.setNewTimer(1.0f);
//                break;
//            case 3:
//                m_timer.setNewTimer(0.8f);
//                break;
//            case 4:
//                m_timer.setNewTimer(0.6f);
//                break;
//            case 5:
//                m_timer.setNewTimer(0.4f);
//                break;
//            }
//        }
//    };
//
//    new PhaseBasedAttacks(phaseAttackSequence);
//
//    BossAI::HealthPercentageNode* health80Check = new BossAI::HealthPercentageNode(mainSequence, 80.0f);
//    BT::Sequence* phase2Sequence = new BT::Sequence(health80Check);
//    BossAI::MoveBossNode* phase2Move = new BossAI::MoveBossNode(phase2Sequence, 400.0f);
//
//    BossAI::HealthPercentageNode* health60Check = new BossAI::HealthPercentageNode(mainSequence, 60.0f);
//    BT::Sequence* phase3Sequence = new BT::Sequence(health60Check);
//    BossAI::MoveBossNode* phase3Move = new BossAI::MoveBossNode(phase3Sequence, 500.0f);
//
//    BossAI::HealthPercentageNode* health40Check = new BossAI::HealthPercentageNode(mainSequence, 40.0f);
//    BT::Sequence* phase4Sequence = new BT::Sequence(health40Check);
//    BossAI::MoveBossNode* phase4Move = new BossAI::MoveBossNode(phase4Sequence, 600.0f);
//
//    BossAI::HealthPercentageNode* health20Check = new BossAI::HealthPercentageNode(mainSequence, 20.0f);
//    BT::Sequence* phase5Sequence = new BT::Sequence(health20Check);
//    BossAI::MoveBossNode* phase5Move = new BossAI::MoveBossNode(phase5Sequence, 700.0f);
//}