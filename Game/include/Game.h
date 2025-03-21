#pragma once
#include "SceneBase.h"
#include "GameObject.h"
#include "Layer.h"
#include <vector>

//class ISceneBase;
enum class GameState
{
    playing
    , paused
    , gameover
};
class Game : public ISceneBase
{
public:
    Game(sf::RenderWindow* Window, const float& framerate, TextureCache* TextureManager);
    virtual~Game();
    void ProcessInput(const sf::Event& event) override;
    void Update(const float& deltatime) override;
    void Render() override;
    void AddLayer(Layer* layer) override{}
    void RemoveLayer(Layer* layer) override{}
    void ClearListLayer() override{}
    std::vector<Layer*>& GetListLayer() override { return m_layer; }
    const std::vector<Layer*>& GetListLayer() const override { return m_layer; }

private:
    GameState m_gameState;
    Layer* m_backgroundLayer;
    Layer* m_middlegroundLayer;
    Layer* m_foregroundLayer;
    std::vector<Layer*> m_layer;
    Player* m_player;
    Terrain* m_terrain;
    /*PhysicsSystem& m_physics;
    std::vector<Platform> m_platforms;
    std::vector<Enemy> m_enemies;
    std::vector<Collectible> m_collectibles;
    Camera m_camera;
    int m_score;*/
    
};