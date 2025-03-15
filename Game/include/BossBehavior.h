//#pragma once
//#include "BehaviorTree.h"
//#include "IShape.h"
//#include <iostream>
//
//class Boss;
//
//enum class BossMovementPattern
//{
//    Horizontal,
//    Vertical,
//    Diagonal,
//    Random
//};
//
//namespace BossAI
//{
//    template <typename T>
//    class BossBehaviorNode : public BT::BehaviorNodeDecorator<Boss, T>
//    {
//    public:
//        BossBehaviorNode(BT::ICompositeNode* parent)
//            : BT::BehaviorNodeDecorator<Boss, T>(parent) {}
//    };
//
//    class HealthPercentageNode : public BossBehaviorNode<BT::IConditionalNode>
//    {
//    public:
//        HealthPercentageNode(BT::ICompositeNode* parent, float percentage);
//        bool condition() override;
//
//    private:
//        float m_percentage;
//    };
//
//    class TimerNode : public BossBehaviorNode<BT::IConditionalNode>
//    {
//    public:
//        TimerNode(BT::ICompositeNode* parent, float minTime, float maxTime);
//        bool condition() override;
//
//    private:
//        Timer m_timer;
//        float m_minTime;
//        float m_maxTime;
//        bool m_initialized;
//        float m_elapsedTime;
//    };
//
//    class MovementPatternTimerNode : public BossBehaviorNode<BT::IConditionalNode>
//    {
//    public:
//        MovementPatternTimerNode(BT::ICompositeNode* parent, float switchTime);
//        bool condition() override;
//
//    private:
//        Timer m_timer;
//        float m_switchTime;
//        bool m_initialized;
//    };
//
//    class MoveBossNode : public BossBehaviorNode<BT::IActionNode>
//    {
//    public:
//        MoveBossNode(BT::ICompositeNode* parent, float speed);
//        BT::Status tick() override;
//        void display() override;
//
//    private:
//        float m_speed;
//    };
//
//    class MovePatternNode : public BossBehaviorNode<BT::IActionNode>
//    {
//    public:
//        MovePatternNode(BT::ICompositeNode* parent);
//        BT::Status tick() override = 0;
//        void display() override;
//
//    protected:
//        float m_patternPhase;
//        sf::Vector2f calculateTargetPosition();
//    };
//
//    class HorizontalPatternNode : public MovePatternNode
//    {
//    public:
//        HorizontalPatternNode(BT::ICompositeNode* parent);
//        BT::Status tick() override;
//
//    private:
//        sf::Vector2f calculateHorizontalPosition();
//    };
//
//    class VerticalPatternNode : public MovePatternNode
//    {
//    public:
//        VerticalPatternNode(BT::ICompositeNode* parent);
//        BT::Status tick() override;
//
//    private:
//        sf::Vector2f calculateVerticalPosition();
//    };
//
//    class DiagonalPatternNode : public MovePatternNode
//    {
//    public:
//        DiagonalPatternNode(BT::ICompositeNode* parent);
//        BT::Status tick() override;
//
//    private:
//        sf::Vector2f calculateDiagonalPosition();
//    };
//
//    class FireBossNode : public BossBehaviorNode<BT::IActionNode>
//    {
//    public:
//        FireBossNode(BT::ICompositeNode* parent, int bulletCount, float spreadAngle);
//        BT::Status tick() override;
//        void display() override;
//
//    private:
//        int m_bulletCount;
//        float m_spreadAngle;
//    };
//
//    class SpecialAttackNode : public BossBehaviorNode<BT::IActionNode>
//    {
//    public:
//        SpecialAttackNode(BT::ICompositeNode* parent);
//        BT::Status tick() override = 0;
//        void display() override;
//    };
//
//    class RegenerateHealthNode : public SpecialAttackNode
//    {
//    public:
//        RegenerateHealthNode(BT::ICompositeNode* parent, float amount);
//        BT::Status tick() override;
//
//    private:
//        float m_amount;
//    };
//
//    class FireGrowingProjectileNode : public SpecialAttackNode
//    {
//    public:
//        FireGrowingProjectileNode(BT::ICompositeNode* parent);
//        BT::Status tick() override;
//    };
//
//    class FireFastProjectileNode : public SpecialAttackNode
//    {
//    public:
//        FireFastProjectileNode(BT::ICompositeNode* parent);
//        BT::Status tick() override;
//    };
//
//    class ActivateShieldNode : public SpecialAttackNode
//    {
//    public:
//        ActivateShieldNode(BT::ICompositeNode* parent, float duration);
//        BT::Status tick() override;
//
//    private:
//        float m_duration;
//    };
//
//    class BoostDamageNode : public SpecialAttackNode
//    {
//    public:
//        BoostDamageNode(BT::ICompositeNode* parent, float multiplier, float duration);
//        BT::Status tick() override;
//
//    private:
//        float m_multiplier;
//        float m_duration;
//    };
//
//    class RandomAttackSelector : public BossBehaviorNode<BT::ICompositeNode>
//    {
//    public:
//        RandomAttackSelector(BT::ICompositeNode* parent);
//        BT::Status tick() override;
//        void display() override;
//    };
//
//    class RandomMovementSelector : public BossBehaviorNode<BT::ICompositeNode>
//    {
//    public:
//        RandomMovementSelector(BT::ICompositeNode* parent);
//        BT::Status tick() override;
//        void display() override;
//        void setCurrentPattern(BossMovementPattern pattern);
//
//    private:
//        BossMovementPattern m_currentPattern;
//    };
//
//    class NormalAttackTimerNode : public BossBehaviorNode<BT::IConditionalNode>
//    {
//    public:
//        NormalAttackTimerNode(BT::ICompositeNode* parent, float fireRate);
//        bool condition() override;
//
//    private:
//        Timer m_timer;
//        float m_fireRate;
//    };
//}