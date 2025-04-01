//#pragma once
//#include "IGameObject.h"
//#include "GameObject.h"
//#include <map>
//
//
//
//
//
//enum class ZombieClassicState
//{
//	  DEAD
//	, LIVE
//	, WALKING
//	, RUNNING 
//	, ATTACK
//	, SEEKING
//	, PROWLING
//	, IDLE
//	, FOLLOW
//};
//
//enum class ZombieVomitoState
//{
//	  DEAD
//	, LIVE
//	, WALKING
//	, RUNNING
//	, ATTACK
//	, SEEKING
//	, PROWLING
//	, IDLE
//	, FOLLOW
//};
//
//enum class ZombieTankState
//{
//	  DEAD
//	, LIVE
//	, WALKING
//	, RUNNING
//	, ATTACK
//	, SEEKING
//	, PROWLING
//	, IDLE
//	, FOLLOW
//};
//
//enum class NecromancerState
//{
//	  DEAD
//	, WALKING //Ou FLYING
//	, ATTACK
//	, SEEKING
//	, RETIRE
//	, IDLE
//	, FOLLOW
//};
//
//
//enum class PlayerState
//{
//	DEAD
//	, LIVE
//	, IDLE
//	, WALKING
//	, RUNNING
//	, ATTACK
//	, CAST_SPELL
//};
//
//
//class StatPlayerDead;
//
//class PlayerStateMachine : public IComposite
//{
//public:
//	PlayerStateMachine(Player* player, PlayerState currentState)
//		:IComposite(player)
//		,m_player(player)
//		,m_currentState(currentState)
//	{
//		// m_playerDead = new StatPlayerDead(this);
//	}
//	~PlayerStateMachine()
//	{
//		if (m_playerDead != nullptr)
//		{
//			delete m_playerDead;
//			m_playerDead = nullptr;
//		}
//	}
//	void TransitionTo(PlayerState newState);
//	void update(float deltaTime);
//	Player* getPlayer() { return m_player; }
//private:
//	Player* m_player;
//	StatPlayerDead* m_playerDead;
//	PlayerState m_currentState;
//
//	// Ajouter un conteneur pour tous les états
//	//std::map<PlayerState, IPlayerState*> m_states;
//
//	// Éventuellement un historique des états
//	// std::stack<PlayerState> m_stateHistory;
//};
//
//class IPlayerState : public ILeaf
//{
//public:
//	IPlayerState(IComposite* parent) 
//		: ILeaf(parent)
//	{ }
//	virtual ~IPlayerState() = default;
//	virtual void enter() = 0 ;
//	virtual void update() = 0 ;
//	virtual void exit() = 0 ;
//	virtual void Update(const float& deltatime) = 0 ;
//	virtual void ProcessInput(const sf::Event& event) = 0 ;
//	virtual void Render() = 0 ;
//
//protected:
//
//};
//
//
//// Peut accéder au Player via la StateMachine avec getPlayer() quand nécessaire
//class StatPlayerDead : public IPlayerState
//{
//public:
//	StatPlayerDead(PlayerStateMachine* stateMachine);
//	virtual ~StatPlayerDead() = default;
//	void enter() override;
//	void update() override;
//	void exit() override;
//	void Update(const float& deltatime) override;
//	void ProcessInput(const sf::Event& event) override;
//	void Render() override;
//
//private:
//	PlayerStateMachine* m_playerStateMachine;
//};