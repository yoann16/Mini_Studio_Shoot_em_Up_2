#include "EntityType.h"


//void Player::Update(const float& deltatime)
//{ }
//void Player::ProcessInput(const sf::Event& event)
//{ }
//void Player::Render()
//{
//
//}
sf::Vector2f initPosition = { 0,0 };
DEFINE_GAME_OBJECT(Player, m_initialPosition, LayersType::Middleground, 0b1011)

//DEFINE_GAME_OBJECT(Player,Position,1,0b1101)
