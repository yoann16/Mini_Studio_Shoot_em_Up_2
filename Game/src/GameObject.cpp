#include "GameObject.h"

Player::Player(const sf::Vector2f& initposition)
	: m_initialPosition(initposition)
	, m_currentPosition(initposition)
{
}
void Player::Update(const float& deltatime)
{ }
void Player::ProcessInput(const sf::Event& event)
{ }
void Player::Render()
{ }
sf::Vector2f initPosition = { 0,0 };
DEFINE_GAME_OBJECT(Player, initPosition, LayersType::Middleground, 0b1011)
//DEFINE_GAME_OBJECT(Player,Position,1,0b1101)
