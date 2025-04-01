#pragma once
#include "IGameObject.h"
class IShapeSFML;
class TextureCache;
class StaticSpriteSheet;
namespace Decor
{
    enum class Tree
    {
        Spawn,

        PinkLarge,
        PinkMedium,
        PinkSmall,
        PinkDead,
        PinkShrub,

        GreenLarge,
        GreenMedium,
        GreenSmall,
        GreenShrub,

        WhiteLarge,
        WhiteMedium,
        WhiteSmall,
        WhiteDead,
        WhiteShrub
    };
    enum class Bush
    {
        PinkLarge,
        PinkMedium,
        PinkSmall,

        GreenLarge,
        GreenMedium,
        GreenSmall,

        WhiteLarge,
        WhiteMedium,
        WhiteSmall
    };
    enum class Mushroom
    {
        Red,
        Pink
    };
    enum class Flowers
    {
        White,
        MixedPurpleBlue,
        MixedPurpleRed,
        DeepYellow,
        PaleYellow,
        BlueThree,
        BlueTwo,
        PurpleThree,
        PurpleTwo
    };
    enum class Trunk_of_Tree
    {
        Classic,
        Corrupt
    };
    enum class Rock
    {
        Large,
        Medium,
        Small
    };
    enum class Easter_Egg
    {
        First,
        Second
    };
}

class Tree :public IGameObject
{
public:
    DECLARE_GAME_OBJECT();
    Tree(Decor::Tree typeTree, const sf::Vector2f& Position, TextureCache& textureCache);
    ~Tree();
    float sorting_Y_point() const;
    void SetHitboxDimensions(Decor::Tree treeType);
    void SetSpriteParameters(Decor::Tree treeType);
    void Update(const float& deltatime);
    void ProcessInput(const sf::Event& event);
    void Render();
    
private:
    Decor::Tree m_tree;
    IShapeSFML* m_shape;
    TextureCache& m_textureCache;
    StaticSpriteSheet* m_SpriteSheet;
    float m_width;
    float m_height;
    float m_hitboxWidth;
    float m_hitboxHeight;
};

class Bush :public IGameObject
{
public:
    DECLARE_GAME_OBJECT();
    Bush(Decor::Bush typeBush, const sf::Vector2f& Position, TextureCache& textureCache);
    ~Bush();
    float sorting_Y_point() const;
    void SetHitboxDimensions(Decor::Bush typeBush);
    void SetSpriteParameters(Decor::Bush typeBush);
    void Update(const float& deltatime);
    void ProcessInput(const sf::Event& event);
    void Render();

private:
    Decor::Bush m_bush;
    IShapeSFML* m_shape;
    TextureCache& m_textureCache;
    StaticSpriteSheet* m_SpriteSheet;
    float m_width;
    float m_height;
    float m_hitboxWidth;
    float m_hitboxHeight;
};