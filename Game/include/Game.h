#pragma once
#pragma once
#include "SceneBase.h"
#include "GameObject.h"
class ISceneBase;
enum class GameState
{
    playing
    , paused
    , gameover
};
class Game : public ISceneBase
{
public:
    Game(sf::RenderWindow* Window, const float& framerate, TextureCache* TextureManager)
        :ISceneBase(Window, framerate, TextureManager)
        , m_gameState(GameState::playing)
    {
        sf::Vector2f winSize(getWindow()->getSize().x, getWindow()->getSize().y);

        m_Background = new RectangleSFML(winSize.x, winSize.y, sf::Vector2f(winSize.x/2, winSize.y/2));
        m_Background->setTexture(m_texture->getTexture("j.png"));
        m_Background->getShape().setScale(1.0f, 1.0f);

        sf::Vector2f initialPosition = GetCenterWindow();
        m_player = new Player(this, 10.0f, initialPosition);
        
    }
    virtual ~Game() = default;
    void ProcessInput(const sf::Event& event) override
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
    void Update(const float& deltatime) override
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

    }
    void Render() override
    {
        getWindow()->draw(m_Background->getShape());
        m_player->Render();
        if (m_gameState == GameState::paused)
        {
        }
    }

private:
    /*void InitializeLevel();
    void UpdateCamera();
    void HandleGameLogic();*/
private:
    Player* m_player;
    /*PhysicsSystem& m_physics;
    std::vector<Platform> m_platforms;
    std::vector<Enemy> m_enemies;
    std::vector<Collectible> m_collectibles;
    Camera m_camera;
    int m_score;*/
    GameState m_gameState;
};