//#include "BossBullet.h"
//#include "Ship.h"
//
//EntityProjectileBase::EntityProjectileBase(AnimateSprite animate, IComposite* scene, ITurret* gun, float angle, float speed, float size, float hp)
//    : IBullet(animate, scene, gun, angle, speed, size, hp)
//    , m_animationTimer(0.15f)
//    , m_absolutePosition(gun->getShape()->getPosition())
//    , m_useAbsolutePosition(true)
//{
//}
//
//void EntityProjectileBase::Update(const float& deltatime)
//{
//    float angleRad = convertDegToRad(m_gunangle);
//    sf::Vector2f movement(
//        std::cos(angleRad) * m_speed * m_scene->getRoot()->getScene()->getRefreshTime().asSeconds(),
//        std::sin(angleRad) * m_speed * m_scene->getRoot()->getScene()->getRefreshTime().asSeconds()
//    );
//
//    if (m_useAbsolutePosition) {
//        m_absolutePosition += movement;
//
//        sf::Vector2f centerOffset = m_scene->getRoot()->getScene()->getBackgroundCenter();
//
//        sf::Vector2f screenPos = m_absolutePosition - centerOffset + m_scene->getRoot()->getScene()->GetCenterWindow();
//
//        m_shape->setPosition(screenPos);
//
//        m_gunPosition = screenPos;
//    }
//    else {
//        m_gunPosition += movement;
//        m_shape->setPosition(m_gunPosition);
//    }
//
//    updateAnimation(deltatime);
//}
//
//void EntityProjectileBase::updateAnimation(const float& deltaTime)
//{
//    if (m_animationTimer.AutoActionIsReady(m_scene->getRoot()->getScene()->getRefreshTime().asSeconds())) {
//        m_animate.ChangeToNextPath();
//        m_shape->setTexture(m_scene->getRoot()->getScene()->getTexture()->getTexture(m_animate.getCurrentPath()));
//    }
//}
//
//void EntityProjectileBase::HandleCollision(IGameObject* object)
//{
//    if (object->globalGameObjectType() != GameObjectType::DestructibleObject)
//        return;
//
//    if (shouldIgnoreCollision(object))
//        return;
//
//    ChangeLife(-1);
//}
//
//bool EntityProjectileBase::shouldIgnoreCollision(IGameObject* object) const
//{
//    return getObj<EntityProjectileBase*>(object) != nullptr;
//}
//
//EntityProjectile::EntityProjectile(IComposite* scene, ITurret* gun, float angle, float speed, float size)
//    : EntityProjectileBase({ "PlayerBullet.png", "PlayerBullet2.png" }, scene, gun, angle, speed, size, 1.0f)
//{
//    m_shape = new CircleSFML(size, m_gunPosition);
//    m_shape->setTexture(m_scene->getRoot()->getScene()->getTexture()->getTexture(m_animate.getCurrentPath()));
//    m_shape->setRotation(m_gunangle);
//}
//
//void EntityProjectile::Render()
//{
//    m_scene->getRoot()->getScene()->getWindow()->draw(static_cast<CircleSFML*>(m_shape)->getShape());
//}
//
//LargeProjectile::LargeProjectile(IComposite* scene, ITurret* gun, float angle, float speed, float size, float damage)
//    : EntityProjectileBase({ "PlayerBullet.png", "PlayerBullet2.png" }, scene, gun, angle, speed, size, damage)
//    , m_lifetimeTimer(3.0f)
//    , m_damage(damage)
//{
//    m_shape = new CircleSFML(size, m_gunPosition);
//    m_shape->setTexture(m_scene->getRoot()->getScene()->getTexture()->getTexture(m_animate.getCurrentPath()));
//    m_shape->setRotation(m_gunangle);
//
//    m_useAbsolutePosition = true;
//}
//
//void LargeProjectile::Render()
//{
//    m_scene->getRoot()->getScene()->getWindow()->draw(static_cast<CircleSFML*>(m_shape)->getShape());
//}
//
//void LargeProjectile::Update(const float& deltatime)
//{
//    EntityProjectileBase::Update(deltatime);
//
//    m_lifetimeTimer.NextTIck(deltatime);
//    if (m_lifetimeTimer.ActionIsReady()) {
//        destroy();
//    }
//}
//
//bool LargeProjectile::shouldIgnoreCollision(IGameObject* object) const
//{
//    return getObj<LargeProjectile*>(object) != nullptr || EntityProjectileBase::shouldIgnoreCollision(object);
//}
//
//FastProjectile::FastProjectile(AnimateSprite animate, IComposite* scene, ITurret* gun, float angle, float speed, float size, float hp)
//    : EntityProjectileBase(animate, scene, gun, angle, speed, size, hp)
//{
//    m_shape = new SquareSFML(size, m_gunPosition);
//    m_shape->setTexture(m_scene->getRoot()->getScene()->getTexture()->getTexture(m_animate.getCurrentPath()));
//    m_shape->setRotation(m_gunangle);
//}
//
//void FastProjectile::Render()
//{
//    m_scene->getRoot()->getScene()->getWindow()->draw(static_cast<SquareSFML*>(m_shape)->getShape());
//}
//
//bool FastProjectile::shouldIgnoreCollision(IGameObject* object) const
//{
//    return getObj<FastProjectile*>(object) != nullptr || EntityProjectileBase::shouldIgnoreCollision(object);
//}
//
//ShieldProjectile::ShieldProjectile(IComposite* scene, IShapeSFML* owner, float duration, float radius)
//    : DestructibleObject(scene, 100.0f)
//    , ILeaf(scene)
//    , m_owner(owner)
//    , m_animate({ "PlayerBulle.png", "PlayerBulle.png" })
//    , m_duration(duration)
//    , m_pulseTimer(0.2)
//    , m_radius(radius)
//    , m_initialRadius(radius)
//    , m_growing(true)
//{
//    m_shape = new CircleSFML(m_radius, m_owner->getPosition());
//    m_shape->setTexture(m_scene->getRoot()->getScene()->getTexture()->getTexture(m_animate.getCurrentPath()));
//}
//
//void ShieldProjectile::Render()
//{
//    m_scene->getRoot()->getScene()->getWindow()->draw(static_cast<CircleSFML*>(m_shape)->getShape());
//}
//
//void ShieldProjectile::Update(const float& deltatime)
//{
//    m_shape->setPosition(m_owner->getPosition());
//
//    if (m_pulseTimer.AutoActionIsReady(m_scene->getRoot()->getScene()->getRefreshTime().asSeconds())) {
//        m_animate.ChangeToNextPath();
//        m_shape->setTexture(m_scene->getRoot()->getScene()->getTexture()->getTexture(m_animate.getCurrentPath()));
//
//        if (m_growing) {
//            m_radius += 2.0f;
//            if (m_radius >= m_initialRadius * 1.2f) {
//                m_growing = false;
//            }
//        }
//        else {
//            m_radius -= 2.0f;
//            if (m_radius <= m_initialRadius * 0.9f) {
//                m_growing = true;
//            }
//        }
//
//        m_shape->setSize(sf::Vector2f(m_radius * 2, m_radius * 2));
//    }
//
//    m_duration.NextTIck(m_scene->getRoot()->getScene()->getRefreshTime().asSeconds());
//    if (m_duration.ActionIsReady()) {
//        destroy();
//    }
//}
//
//void ShieldProjectile::HandleCollision(IGameObject* object)
//{
//    if (object->globalGameObjectType() != GameObjectType::DestructibleObject)
//        return;
//
//    ClassicBullet* bullet = getObj<ClassicBullet*>(object);
//    if (bullet) {
//        float reflectAngle = bullet->getShape()->getangle() + 180.0f;
//        ITurret* turretOwner = bullet->getTurret();
//        if (turretOwner) {
//            AnimateSprite reflect({ "PlayerBulle.png" });
//            new ClassicBullet(reflect, m_scene, turretOwner, reflectAngle, 1000.0f, 10.0f, 1.0f);
//        }
//        bullet->destroy();
//    }
//}