#include "Game.h"


Game::Game(sf::RenderWindow* Window, const float& framerate, TextureCache* TextureManager)
    :ISceneBase(Window, framerate, TextureManager)
    , m_gameState(GameState::playing)
{

    m_backgroundLayer = new Layer(this, LayersType::Background,0);
    m_middlegroundLayer = new Layer(this, LayersType::Middleground,1);
    m_foregroundLayer = new Layer(this, LayersType::Foreground,2);

    const sf::Vector2f windowCenter = sf::Vector2f(
        Window->getSize().x / 2.0f,
        Window->getSize().y / 2.0f
    );
    const sf::Vector2f treePosition =  sf::Vector2f(300.0f, 500.0f);

    m_terrain = new Terrain(m_backgroundLayer, windowCenter);
    m_player = new Player(m_middlegroundLayer, 10.0f, windowCenter);
    m_treetrunk = new TreeTrunk(m_middlegroundLayer, treePosition);
    m_treeleave = new TreeLeave(m_foregroundLayer, treePosition);
    

    m_backgroundLayer->AddGameObject(m_terrain);
    m_middlegroundLayer->AddGameObject(m_player);
    m_middlegroundLayer->AddGameObject(m_treetrunk);
    m_foregroundLayer->AddGameObject(m_treeleave);


}
//Game::~Game()
//{
//    delete m_backgroundLayer;
//    delete m_middlegroundLayer;
//    delete m_foregroundLayer;
//    delete m_terrain;
//    delete m_player;
//}
void Game::ProcessInput(const sf::Event& event) 
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::P)
        {
            if (m_gameState == GameState::playing)
                m_gameState = GameState::paused;
            else if (m_gameState == GameState::paused)
                m_gameState = GameState::playing;

        }

    }
    m_player->ProcessInput(event);

}
void Game::Update(const float& deltatime) 
{
    //std::cout << "GameState: " << static_cast<int>(m_gameState) << std::endl;
    switch (m_gameState)
    {
    case GameState::playing:
    {

        m_player->Update(deltatime);
        break;

    }
    case GameState::paused:
    {

        //faire un truc
        break;

    }
    case GameState::gameover:
    {

        //faire un truc
        break;

    }
    }

    m_backgroundLayer->Update(deltatime);
    m_middlegroundLayer->Update(deltatime);
    m_foregroundLayer->Update(deltatime);
}
void Game::Render() 
{
    m_backgroundLayer->Render();
    m_middlegroundLayer->Render();
    m_foregroundLayer->Render();
    if (m_gameState == GameState::paused)
    {
    }
}