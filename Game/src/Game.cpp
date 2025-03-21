#include "Game.h"
#include "Collision.h"


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
    const sf::Vector2f patrol =  sf::Vector2f(windowCenter.x, windowCenter.y - 300.0f);


    m_terrain = new Terrain(m_backgroundLayer, windowCenter);
    m_player = new Player(m_middlegroundLayer, 10.0f, windowCenter);
    m_treetrunk = new TreeTrunk(m_middlegroundLayer, treePosition);
    m_zombie = new ZombieSeed(m_middlegroundLayer, 10.f, patrol);
   auto  m_treeleave = new TreeLeave(m_foregroundLayer, treePosition);
    

    m_backgroundLayer->AddGameObject(m_terrain);
    m_middlegroundLayer->AddGameObject(m_player);
    m_middlegroundLayer->AddGameObject(m_treetrunk);
    m_middlegroundLayer->AddGameObject(m_zombie);
    m_middlegroundLayer->AddGameObject(m_treeleave);
    ////m_gameObject.push_back(m_terrain);
    //m_gameObject.push_back(m_player);
    //m_gameObject.push_back(m_treetrunk);
    //m_gameObject.push_back(m_treeleave);

    m_zombie->SetTargetPlayer(m_player);
}

Game::~Game()
{
    delete m_backgroundLayer;
    delete m_middlegroundLayer;
    delete m_foregroundLayer;
    /*delete m_terrain;
    delete m_player;*/
}

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
    if (m_player)
    {
        m_player->ProcessInput(event);
    }

}
void Game::Update(const float& deltatime) 
{
    //std::cout << "GameState: " << static_cast<int>(m_gameState) << std::endl;
    switch (m_gameState)
    {
    case GameState::playing:
    {
        sf::Vector2f previousPosition;
        if (m_player != nullptr && m_treetrunk != nullptr && m_zombie != nullptr)
        {
            sf::Vector2f previousPosition = m_player->getShape()->getPosition();
            m_player->Update(deltatime);
            m_zombie->Update(deltatime);

            AABB playerBox = m_player->getShape()->GetBoundingBox();
            AABB treeBox = m_treetrunk->getShape()->GetBoundingBox();

            if (CheckCollsion(playerBox, treeBox))
            {
                
                m_player->getShape()->setPosition(previousPosition);

                
                m_player->setdirection({ 0.0f, 0.0f });
            }
        }
        /*if (m_zombie)
        {

            m_zombie->Update(deltatime);
        }
        
        if (m_player != nullptr && m_treetrunk != nullptr && m_zombie != nullptr)
        {
            AABB playerBox = m_player->getShape()->GetBoundingBox();
            AABB treeBox = m_treetrunk->getShape()->GetBoundingBox();
            AABB zombie = m_zombie->getShape()->GetBoundingBox();

            if (CheckCollsion(playerBox, treeBox)) 
            {
                std::cout << "Collision détectée!" << std::endl;
                std::cout << "Player: (" << playerBox.Amin.x << "," << playerBox.Amin.y << ") - ("
                    << playerBox.Amax.x << "," << playerBox.Amax.y << ")" << std::endl;
                std::cout << "Tree: (" << treeBox.Amin.x << "," << treeBox.Amin.y << ") - ("
                    << treeBox.Amax.x << "," << treeBox.Amax.y << ")" << std::endl;
                m_player->getShape()->setPosition(previousPosition);
            }
        }*/



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