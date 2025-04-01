#pragma once
#include <vector>
#include "EntityType.h"
#include "DecorType.h"
#include "SceneBase.h"


class Layer;
enum class GameState
{
    playing
    , paused
    , gameover
};
class GameScene : public ISceneBase
{
public:
    GameScene(sf::RenderWindow* Window, const float& framerate, TextureCache* TextureManager)
        :ISceneBase(Window, framerate, TextureManager)
        , m_texture(*TextureManager)
    {
        m_backgroundLayer = new Layer(LayersType::Background, 0);
        m_middleLayer = new Layer(LayersType::Middleground, 1);
        m_foregroundLayer = new Layer(LayersType::Foreground, 2);
        const sf::Vector2f windowCenter = sf::Vector2f(
            Window->getSize().x / 2.0f,
            Window->getSize().y / 2.0f
        );
        //m_player = new Player(windowCenter, m_texture);
        m_decor = new Bush(Decor::Bush::PinkSmall, windowCenter, m_texture);

        AddLayer(m_backgroundLayer);
        AddLayer(m_middleLayer);
        AddLayer(m_foregroundLayer);

        m_middleLayer->AddGameObject(m_decor);
    }

    ~GameScene()
    {
        ClearListLayer();
    }

    void Update(const float& deltatime) override
    {
        m_backgroundLayer->Update(deltatime);
        m_middleLayer->Update(deltatime);
        m_foregroundLayer->Update(deltatime);
    }
    void ProcessInput(const sf::Event& event)override
    {
        m_backgroundLayer->ProcessInput(event);
        m_middleLayer->ProcessInput(event);
        m_foregroundLayer->ProcessInput(event);
    }
    void Render()override
    {
        m_backgroundLayer->Render();
        m_middleLayer->Render();
        m_foregroundLayer->Render();
    }
    /*void Create_and_AddGameObject_ToLayer(TextureCache& texture)
    {
        sf::Vector2f initPosition = { 500.0f,500.0f };
        m_player = new Player(initPosition);
        m_middleLayer->AddGameObject(m_player);
    }*/
private:
    Layer* m_backgroundLayer;
    Layer* m_middleLayer;
    Layer* m_foregroundLayer;
    //Player* m_player;
    Bush* m_decor;
    TextureCache& m_texture;
};

class GameObjectFactory
{
public:
    GameObjectFactory(GameScene* scene);

    Player* CreatePlayer(TextureCache& texture, const sf::Vector2f& position);
    //Enemy* CreateEnemy(TextureCache& texture, const sf::Vector2f& position);
    //Map*
    //ZombieSeed*
    //Tree*
    //TreeSpawn*
    //// etc.

private:
    void AddToAppropriateLayer(IGameObject* gameObject);

    GameScene* m_scene;
};