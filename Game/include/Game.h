#pragma once
#include <vector>

class ISceneBase;
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
    {
        m_backgroundLayer = new Layer(LayersType::Background, 0);
        m_middleLayer = new Layer(LayersType::Middleground, 1);
        m_foregroundLayer = new Layer(LayersType::Foreground, 2);

        AddLayer(m_backgroundLayer);
        AddLayer(m_middleLayer);
        AddLayer(m_foregroundLayer);
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
private:
    Layer* m_backgroundLayer;
    Layer* m_middleLayer;
    Layer* m_foregroundLayer;
};