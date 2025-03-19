#pragma once
#include "SceneBase.h"
#include "GameObject.h"
#include "Layer.h"
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
    Game(sf::RenderWindow* Window, const float& framerate, TextureCache* TextureManager);
    virtual~Game()=default;
    void ProcessInput(const sf::Event& event) override;
    void Update(const float& deltatime) override;
    void Render() override;

private:
    /*void InitializeLevel();
    void UpdateCamera();
    void HandleGameLogic();*/
private:
    GameState m_gameState;
    Layer* m_backgroundLayer;
    Layer* m_middlegroundLayer;
    Layer* m_foregroundLayer;
    Terrain* m_terrain;
    Player* m_player;
    TreeTrunk* m_treetrunk;
    TreeLeave* m_treeleave;
    /*PhysicsSystem& m_physics;
    std::vector<Platform> m_platforms;
    std::vector<Enemy> m_enemies;
    std::vector<Collectible> m_collectibles;
    Camera m_camera;
    int m_score;*/
    
};