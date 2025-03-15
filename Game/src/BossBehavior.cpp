//#include "BossBehavior.h"
//#include "Boss.h"
//#include "RandomNumber.h"
//
//namespace BossAI
//{
//    HealthPercentageNode::HealthPercentageNode(BT::ICompositeNode* parent, float percentage)
//        : BossBehaviorNode<BT::IConditionalNode>(parent)
//        , m_percentage(percentage)
//    {
//    }
//
//    bool HealthPercentageNode::condition()
//    {
//        float healthPercent = (getGameObject()->getCurrentLife() / getGameObject()->getMaxLife()) * 100.0f;
//        return healthPercent <= m_percentage;
//    }
//
//    TimerNode::TimerNode(BT::ICompositeNode* parent, float minTime, float maxTime)
//        : BossBehaviorNode<BT::IConditionalNode>(parent)
//        , m_timer(0.0f)
//        , m_minTime(minTime)
//        , m_maxTime(maxTime)
//        , m_initialized(false)
//        , m_elapsedTime(0.0f)
//    {
//    }
//
//    bool TimerNode::condition()
//    {
//        if (!m_initialized) {
//            int randomDuration = UseRandomNumber().getRandomNumber<int>(m_minTime, m_maxTime);
//            m_timer.setNewTimer(randomDuration);
//            m_initialized = true;
//            m_elapsedTime = 0.0f;
//        }
//
//        float deltaSeconds = 1.0f / 60.0f;
//        m_timer.NextTIck(deltaSeconds);
//
//        if (m_timer.ActionIsReady()) {
//            m_initialized = false;
//            return true;
//        }
//
//        return false;
//    }
//
//    MovementPatternTimerNode::MovementPatternTimerNode(BT::ICompositeNode* parent, float switchTime)
//        : BossBehaviorNode<BT::IConditionalNode>(parent)
//        , m_timer(switchTime)
//        , m_switchTime(switchTime)
//        , m_initialized(false)
//    {
//    }
//
//    bool MovementPatternTimerNode::condition()
//    {
//        if (!m_initialized) {
//            m_timer.setNewTimer(m_switchTime);
//            m_initialized = true;
//        }
//
//        float deltaSeconds = 1.0f / 60.0f;
//        m_timer.NextTIck(deltaSeconds);
//
//        if (m_timer.ActionIsReady()) {
//            m_initialized = false;
//            return true;
//        }
//
//        return false;
//    }
//
//    MoveBossNode::MoveBossNode(BT::ICompositeNode* parent, float speed)
//        : BossBehaviorNode<BT::IActionNode>(parent)
//        , m_speed(speed)
//    {
//    }
//
//    BT::Status MoveBossNode::tick()
//    {
//        getGameObject()->setSpeed(m_speed);
//        return BT::Success;
//    }
//
//    void MoveBossNode::display()
//    {
//    }
//
//    MovePatternNode::MovePatternNode(BT::ICompositeNode* parent)
//        : BossBehaviorNode<BT::IActionNode>(parent)
//        , m_patternPhase(0.0f)
//    {
//    }
//
//    void MovePatternNode::display()
//    {
//    }
//
//    sf::Vector2f MovePatternNode::calculateTargetPosition()
//    {
//        return sf::Vector2f(0, 0);
//    }
//
//    HorizontalPatternNode::HorizontalPatternNode(BT::ICompositeNode* parent)
//        : MovePatternNode(parent)
//    {
//    }
//
//    BT::Status HorizontalPatternNode::tick()
//    {
//        m_patternPhase += 0.01f;
//        if (m_patternPhase > 6.28f)
//            m_patternPhase = 0.0f;
//
//        sf::Vector2f targetPos = calculateHorizontalPosition();
//
//        getGameObject()->moveToPosition(targetPos);
//
//        return BT::Success;
//    }
//
//    sf::Vector2f HorizontalPatternNode::calculateHorizontalPosition()
//    {
//        auto window = getGameObject()->getScene()->getRoot()->getScene()->getWindow();
//        float windowWidth = window->getSize().x;
//        float windowHeight = window->getSize().y;
//
//        float amplitude = windowWidth * 0.4f;
//        float yPosition = -windowHeight * 0.25f;
//
//        float newX = amplitude * sin(m_patternPhase);
//        return sf::Vector2f(newX, yPosition);
//    }
//
//    VerticalPatternNode::VerticalPatternNode(BT::ICompositeNode* parent)
//        : MovePatternNode(parent)
//    {
//    }
//
//    BT::Status VerticalPatternNode::tick()
//    {
//        m_patternPhase += 0.01f;
//        if (m_patternPhase > 6.28f)
//            m_patternPhase = 0.0f;
//
//        sf::Vector2f targetPos = calculateVerticalPosition();
//
//        getGameObject()->moveToPosition(targetPos);
//
//        return BT::Success;
//    }
//
//    sf::Vector2f VerticalPatternNode::calculateVerticalPosition()
//    {
//        auto window = getGameObject()->getScene()->getRoot()->getScene()->getWindow();
//        float windowWidth = window->getSize().x;
//        float windowHeight = window->getSize().y;
//
//        float amplitude = windowHeight * 0.3f;
//        float xPosition = 0.0f;
//
//        float newY = -windowHeight * 0.3f + amplitude * sin(m_patternPhase);
//        return sf::Vector2f(xPosition, newY);
//    }
//
//    DiagonalPatternNode::DiagonalPatternNode(BT::ICompositeNode* parent)
//        : MovePatternNode(parent)
//    {
//    }
//
//    BT::Status DiagonalPatternNode::tick()
//    {
//        m_patternPhase += 0.01f;
//        if (m_patternPhase > 6.28f)
//            m_patternPhase = 0.0f;
//
//        sf::Vector2f targetPos = calculateDiagonalPosition();
//
//        getGameObject()->moveToPosition(targetPos);
//
//        return BT::Success;
//    }
//
//    sf::Vector2f DiagonalPatternNode::calculateDiagonalPosition()
//    {
//        auto window = getGameObject()->getScene()->getRoot()->getScene()->getWindow();
//        float windowWidth = window->getSize().x;
//        float windowHeight = window->getSize().y;
//
//        float amplitudeX = windowWidth * 0.3f;
//        float amplitudeY = windowHeight * 0.2f;
//
//        float newX = amplitudeX * sin(m_patternPhase);
//        float newY = -windowHeight * 0.3f + amplitudeY * sin(2.0f * m_patternPhase);
//
//        return sf::Vector2f(newX, newY);
//    }
//
//    FireBossNode::FireBossNode(BT::ICompositeNode* parent, int bulletCount, float spreadAngle)
//        : BossBehaviorNode<BT::IActionNode>(parent)
//        , m_bulletCount(bulletCount)
//        , m_spreadAngle(spreadAngle)
//    {
//    }
//
//    BT::Status FireBossNode::tick()
//    {
//        getGameObject()->fireProjectiles(m_bulletCount, m_spreadAngle);
//        return BT::Success;
//    }
//
//    void FireBossNode::display()
//    {
//    }
//
//    SpecialAttackNode::SpecialAttackNode(BT::ICompositeNode* parent)
//        : BossBehaviorNode<BT::IActionNode>(parent)
//    {
//    }
//
//    void SpecialAttackNode::display()
//    {
//    }
//
//    RegenerateHealthNode::RegenerateHealthNode(BT::ICompositeNode* parent, float amount)
//        : SpecialAttackNode(parent)
//        , m_amount(amount)
//    {
//    }
//
//    BT::Status RegenerateHealthNode::tick()
//    {
//        getGameObject()->regenerateHealth(m_amount);
//        return BT::Success;
//    }
//
//    FireGrowingProjectileNode::FireGrowingProjectileNode(BT::ICompositeNode* parent)
//        : SpecialAttackNode(parent)
//    {
//    }
//
//    BT::Status FireGrowingProjectileNode::tick()
//    {
//        getGameObject()->fireSpecialProjectile(ProjectileType::Large);
//        return BT::Success;
//    }
//
//    FireFastProjectileNode::FireFastProjectileNode(BT::ICompositeNode* parent)
//        : SpecialAttackNode(parent)
//    {
//    }
//
//    BT::Status FireFastProjectileNode::tick()
//    {
//        getGameObject()->fireFastProjectile();
//        return BT::Success;
//    }
//
//    ActivateShieldNode::ActivateShieldNode(BT::ICompositeNode* parent, float duration)
//        : SpecialAttackNode(parent)
//        , m_duration(duration)
//    {
//    }
//
//    BT::Status ActivateShieldNode::tick()
//    {
//        return BT::Success;
//    }
//
//    BoostDamageNode::BoostDamageNode(BT::ICompositeNode* parent, float multiplier, float duration)
//        : SpecialAttackNode(parent)
//        , m_multiplier(multiplier)
//        , m_duration(duration)
//    {
//    }
//
//    BT::Status BoostDamageNode::tick()
//    {
//        getGameObject()->activateOffensiveBoost(m_multiplier, m_duration);
//        return BT::Success;
//    }
//
//    RandomAttackSelector::RandomAttackSelector(BT::ICompositeNode* parent)
//        : BossBehaviorNode<BT::ICompositeNode>(parent)
//    {
//    }
//
//    BT::Status RandomAttackSelector::tick()
//    {
//        if (getChildren().empty())
//            return BT::Success;
//
//        int randomIndex = UseRandomNumber().getRandomNumber<int>(0, static_cast<int>(getChildren().size()) - 1);
//        return getChildren()[randomIndex]->tick();
//    }
//
//    void RandomAttackSelector::display()
//    {
//        for (auto& child : getChildren())
//            child->display();
//    }
//
//    RandomMovementSelector::RandomMovementSelector(BT::ICompositeNode* parent)
//        : BossBehaviorNode<BT::ICompositeNode>(parent)
//        , m_currentPattern(BossMovementPattern::Horizontal)
//    {
//    }
//
//    BT::Status RandomMovementSelector::tick()
//    {
//        if (getChildren().empty())
//            return BT::Success;
//
//        int patternIndex = static_cast<int>(m_currentPattern);
//        if (patternIndex >= 0 && patternIndex < getChildren().size()) {
//            return getChildren()[patternIndex]->tick();
//        }
//
//        return getChildren()[0]->tick();
//    }
//
//    void RandomMovementSelector::display()
//    {
//        for (auto& child : getChildren())
//            child->display();
//    }
//
//    void RandomMovementSelector::setCurrentPattern(BossMovementPattern pattern)
//    {
//        m_currentPattern = pattern;
//    }
//
//    NormalAttackTimerNode::NormalAttackTimerNode(BT::ICompositeNode* parent, float fireRate)
//        : BossBehaviorNode<BT::IConditionalNode>(parent), m_timer(fireRate), m_fireRate(fireRate)
//    {
//    }
//
//    bool NormalAttackTimerNode::condition()
//    {
//        float deltaSeconds = 1.0f / 60.0f;
//        m_timer.NextTIck(deltaSeconds);
//
//        if (m_timer.ActionIsReady()) {
//            m_timer.setNewTimer(m_fireRate);
//            return true;
//        }
//        return false;
//    }
//}