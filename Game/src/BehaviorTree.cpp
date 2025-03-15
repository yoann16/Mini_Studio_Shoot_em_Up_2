//#include "BehaviorTree.h"
//
//namespace BT
//{
//    IComponentNode::IComponentNode(ICompositeNode* parent)
//        : m_parent(nullptr)
//    {
//        setParent(parent);
//    }
//
//    IComponentNode::~IComponentNode()
//    {
//        setParent(nullptr);
//    }
//
//    void IComponentNode::setParent(ICompositeNode* newParent)
//    {
//        if (m_parent)
//            m_parent->remove(this);
//
//        m_parent = newParent;
//
//        if (m_parent)
//            m_parent->add(this);
//    }
//
//    ICompositeNode* IComponentNode::getParent() { return m_parent; }
//    const ICompositeNode* IComponentNode::getParent() const { return m_parent; }
//
//    IGameObject* IComponentNode::getGameObject()
//    {
//        return getRootNode()->getGameObject();
//    }
//
//    const IGameObject* IComponentNode::getGameObject() const
//    {
//        return getRootNode()->getGameObject();
//    }
//
//    RootNode* IComponentNode::getRootNode()
//    {
//        auto* currentPtr = this;
//        while (currentPtr->getParent() != nullptr)
//            currentPtr = currentPtr->getParent();
//
//        return static_cast<RootNode*>(currentPtr);
//    }
//
//    const RootNode* IComponentNode::getRootNode() const
//    {
//        const auto* currentPtr = this;
//        while (currentPtr->getParent() != nullptr)
//            currentPtr = currentPtr->getParent();
//
//        return static_cast<const RootNode*>(currentPtr);
//    }
//}