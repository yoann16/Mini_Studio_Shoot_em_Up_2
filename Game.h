#pragma once
#include "SceneBase.h"
#include "GameObject.h"
#include "Map.h"
#include <SFML/Graphics.hpp>

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
        , m_mapView(Window->getDefaultView())
    {
        Map mapAssembler;
        mapAssembler.assemblePngImages("map_complete.png");

        sf::Vector2f winSize(getWindow()->getSize().x, getWindow()->getSize().y);

        m_Background = new RectangleSFML(4000, 4000, sf::Vector2f(2000, 2000));
        m_Background->setTexture(m_texture->getTexture("map_complete.png"));
        m_Background->getShape().setScale(2.0f, 2.0f);

        sf::Vector2f initialPosition = GetCenterWindow();
        m_player = new Player(this, 10.0f, initialPosition);

        m_mapView.setSize(winSize);
        m_mapView.setCenter(initialPosition);
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
        switch (m_gameState)
        {
        case GameState::playing:
        {
            m_player->Update(deltatime);

            sf::Vector2f playerPos = m_player->GetPosition(); 
            m_mapView.setCenter(playerPos);

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
        sf::View defaultView = getWindow()->getView();

        getWindow()->setView(m_mapView);

        getWindow()->draw(m_Background->getShape());
        m_player->Render();

        getWindow()->setView(defaultView);

        if (m_gameState == GameState::paused)
        {
        }
    }

private:
    sf::View m_mapView;
    Player* m_player;
    GameState m_gameState;
};