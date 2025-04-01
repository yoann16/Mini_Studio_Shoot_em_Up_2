#include "DecorType.h"
#include "TextureCache.h"
#include "IShape.h"
#include "Layer.h"
#include "SceneBase.h"
#include "SpriteSheet.h"

Tree:: Tree(Decor::Tree typeTree, const sf::Vector2f& Position, TextureCache& textureCache)
    : m_initialPosition(Position)
    , m_currentPosition(Position)
    , m_textureCache(textureCache)
    , m_tree(typeTree)
    , m_hitboxWidth(0.0f)
    , m_hitboxHeight(0.0f)
{
    SetHitboxDimensions(typeTree);
    m_shape = new RectangleSFML(m_hitboxWidth, m_hitboxHeight, Position);
    m_SpriteSheet = new StaticSpriteSheet(&textureCache, sf::Vector2i(891, 1638));
    SetSpriteParameters(typeTree);
}
Tree::~Tree()
{
    delete m_shape;
    m_shape = nullptr;
    delete m_SpriteSheet;
    m_SpriteSheet = nullptr;
}
float Tree::sorting_Y_point() const
{
    return m_shape->getPosition().x - 5, m_shape->getPosition().y + m_hitboxHeight / 2 - 5;
}
void Tree::SetHitboxDimensions(Decor::Tree treeType)
{
    if (treeType == Decor::Tree::PinkLarge || treeType == Decor::Tree::GreenLarge || treeType == Decor::Tree::WhiteLarge)
    {
        m_hitboxWidth = 25.0f;
        m_hitboxHeight = 35.0f;
    }
    else if (treeType == Decor::Tree::PinkMedium || treeType == Decor::Tree::GreenMedium || treeType == Decor::Tree::WhiteMedium)
    {
        m_hitboxWidth = 25.0f;
        m_hitboxHeight = 35.0f;
    }
    else if (treeType == Decor::Tree::PinkShrub || treeType == Decor::Tree::GreenShrub || treeType == Decor::Tree::WhiteShrub)
    {
        m_hitboxWidth = 10.0f;
        m_hitboxHeight = 30.0f;
    }
    else if (treeType == Decor::Tree::PinkSmall || treeType == Decor::Tree::GreenSmall || treeType == Decor::Tree::WhiteSmall)
    {
        m_hitboxWidth = 10.0f;
        m_hitboxHeight = 35.0f;
    }
    else if (treeType == Decor::Tree::PinkDead || treeType == Decor::Tree::WhiteDead)
    {
        m_hitboxWidth = 10.0f;
        m_hitboxHeight = 50.0f;
    }
    else if (treeType == Decor::Tree::Spawn)
    {
        m_hitboxWidth = 135.0f;
        m_hitboxHeight = 75.0f;
    }
}
void Tree::SetSpriteParameters(Decor::Tree treeType)
{
    m_SpriteSheet->Load("SpriteSheetDecor.png");
    m_SpriteSheet->addRegion(sf::Vector2i(0, 0), sf::Vector2i(7, 6), sf::Vector2i(127, 131));
    m_SpriteSheet->addRegion(sf::Vector2i(0, m_SpriteSheet->getSpriteSheetPixelSize().y - 131 * 6), sf::Vector2i(1, 1), sf::Vector2i(412, 848));
    switch (treeType)
    {
    case Decor::Tree::Spawn:
        m_SpriteSheet->setActiveRegion(1);
        m_SpriteSheet->setFramePosition(0, 0);
        m_SpriteSheet->setOrigin(412/2+25, 848/4);
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Tree::PinkLarge:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(0, 0);
        m_SpriteSheet->setOrigin(127/2+5,131-25);
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Tree::PinkMedium:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(1, 0);
        m_SpriteSheet->setOrigin(127 / 2 + 10, 131 - 30);
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Tree::PinkSmall:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(2, 0);
        m_SpriteSheet->setOrigin(127/2,131-25);
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Tree::PinkDead:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(4, 0);
        m_SpriteSheet->setOrigin(127/2-5,131-35);
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Tree::PinkShrub:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(3, 0);
        m_SpriteSheet->setOrigin(127/2-7,131-50);
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Tree::GreenLarge:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(1, 1);
        m_SpriteSheet->setOrigin(127 / 2 + 5, 131 - 25);
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Tree::GreenMedium:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(2, 1);
        m_SpriteSheet->setOrigin(127 / 2 + 10, 131 - 30);
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Tree::GreenSmall:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(3, 1);
        m_SpriteSheet->setOrigin(127 / 2, 131 - 25);
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Tree::GreenShrub:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(4, 1);
        m_SpriteSheet->setOrigin(127 / 2 - 7, 131 - 50);
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Tree::WhiteLarge:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(1, 2);
        m_SpriteSheet->setOrigin(127 / 2 + 5, 131 - 25);
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Tree::WhiteMedium:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(2, 2);
        m_SpriteSheet->setOrigin(127 / 2 + 10, 131 - 30);
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Tree::WhiteSmall:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(3, 2);
        m_SpriteSheet->setOrigin(127 / 2, 131 - 25);
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Tree::WhiteDead:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(5, 2);
        m_SpriteSheet->setOrigin(127 / 2 - 5, 131 - 35);
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Tree::WhiteShrub:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(4, 2);
        m_SpriteSheet->setOrigin(127 / 2 - 7, 131 - 50);
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    default:
        throw std::runtime_error("no type tree select");
        break;
    }
}
void Tree::Update(const float& deltatime)
{

}
void Tree::ProcessInput(const sf::Event& event)
{

}
void Tree::Render()
{
    Layer* layer = static_cast<Layer*>(getParent());
    layer->getParent();

    ISceneBase* scene = static_cast<ISceneBase*>(layer->getParent());
    scene->getWindow()->draw(m_SpriteSheet->getCurrentFrameSprite());


    RectangleSFML boundingBox(m_shape->getSize().x, m_shape->getSize().y, m_shape->getPosition());
    boundingBox.setFillColor(sf::Color::Transparent);
    boundingBox.setOutlineThickness(2);
    boundingBox.setOutlineColor(sf::Color::Green);

    scene->getWindow()->draw(boundingBox.getShape());

    sf::CircleShape debugPoint(5);
    debugPoint.setFillColor(sf::Color::Red);
    sf::Vector2f sorting_point = { m_shape->getPosition().x-5, m_shape->getPosition().y + m_hitboxHeight / 2 -5};
    debugPoint.setPosition(sorting_point);
    scene->getWindow()->draw(debugPoint);
}
DEFINE_GAME_OBJECT(Tree, m_initialPosition, LayersType::Middleground, 0b1001);


Bush::Bush(Decor::Bush typeBush, const sf::Vector2f& Position, TextureCache& textureCache)
    : m_initialPosition(Position)
    , m_currentPosition(Position)
    , m_textureCache(textureCache)
    , m_bush(typeBush)
    , m_hitboxWidth(0.0f)
    , m_hitboxHeight(0.0f)
{
    SetHitboxDimensions(typeBush);
    m_shape = new RectangleSFML(m_hitboxWidth, m_hitboxHeight, Position);
    m_SpriteSheet = new StaticSpriteSheet(&textureCache, sf::Vector2i(891, 1638));
    SetSpriteParameters(typeBush);
}
Bush::~Bush()
{
    delete m_shape;
    m_shape = nullptr;
    delete m_SpriteSheet;
    m_SpriteSheet = nullptr;
}
float Bush::sorting_Y_point() const
{
    return m_shape->getPosition().x - 5, m_shape->getPosition().y + m_hitboxHeight / 2 - 5;
}
void Bush::SetHitboxDimensions(Decor::Bush typeBush)
{
    if (typeBush == Decor::Bush::PinkLarge || typeBush == Decor::Bush::GreenLarge || typeBush == Decor::Bush::WhiteLarge)
    {
        m_hitboxWidth = 25.0f;
        m_hitboxHeight = 35.0f;
    }
    else if (typeBush == Decor::Bush::PinkMedium || typeBush == Decor::Bush::GreenMedium || typeBush == Decor::Bush::WhiteMedium)
    {
        m_hitboxWidth = 25.0f;
        m_hitboxHeight = 35.0f;
    }
    else if (typeBush == Decor::Bush::PinkSmall || typeBush == Decor::Bush::GreenSmall || typeBush == Decor::Bush::WhiteSmall)
    {
        m_hitboxWidth = 10.0f;
        m_hitboxHeight = 35.0f;
    }
}
void Bush::SetSpriteParameters(Decor::Bush typeBush)
{
    m_SpriteSheet->Load("SpriteSheetDecor.png");
    m_SpriteSheet->addRegion(sf::Vector2i(0, 0), sf::Vector2i(7, 6), sf::Vector2i(127, 131));
    switch (typeBush)
    {
    case Decor::Bush::PinkLarge:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(5, 0);
        m_SpriteSheet->centerOrigin();
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Bush::PinkMedium:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(6, 0);
        m_SpriteSheet->centerOrigin();
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Bush::PinkSmall:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(0, 1);
        m_SpriteSheet->centerOrigin();
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Bush::GreenLarge:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(5, 1);
        m_SpriteSheet->centerOrigin();
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Bush::GreenMedium:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(6, 1);
        m_SpriteSheet->centerOrigin();
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Bush::GreenSmall:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(0, 2);
        m_SpriteSheet->centerOrigin();
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Bush::WhiteLarge:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(6, 3);
        m_SpriteSheet->centerOrigin();
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Bush::WhiteMedium:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(0, 4);
        m_SpriteSheet->centerOrigin();
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    case Decor::Bush::WhiteSmall:
        m_SpriteSheet->setActiveRegion(0);
        m_SpriteSheet->setFramePosition(1, 4);
        m_SpriteSheet->centerOrigin();
        m_SpriteSheet->getCurrentFrameSprite().setPosition(m_currentPosition);
        break;
    default:
        throw std::runtime_error("no type bush select");
        break;
    }
}
void Bush::Update(const float& deltatime)
{

}
void Bush::ProcessInput(const sf::Event& event)
{

}
void Bush::Render()
{
    Layer* layer = static_cast<Layer*>(getParent());
    layer->getParent();

    ISceneBase* scene = static_cast<ISceneBase*>(layer->getParent());
    scene->getWindow()->draw(m_SpriteSheet->getCurrentFrameSprite());


    RectangleSFML boundingBox(m_shape->getSize().x, m_shape->getSize().y, m_shape->getPosition());
    boundingBox.setFillColor(sf::Color::Transparent);
    boundingBox.setOutlineThickness(2);
    boundingBox.setOutlineColor(sf::Color::Green);

    scene->getWindow()->draw(boundingBox.getShape());

    sf::CircleShape debugPoint(5);
    debugPoint.setFillColor(sf::Color::Red);
    sf::Vector2f sorting_point = { m_shape->getPosition().x - 5, m_shape->getPosition().y + m_hitboxHeight / 2 - 5 };
    debugPoint.setPosition(sorting_point);
    scene->getWindow()->draw(debugPoint);
}

DEFINE_GAME_OBJECT(Bush, m_initialPosition, LayersType::Middleground, 0b1001);