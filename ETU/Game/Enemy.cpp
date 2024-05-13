#include "stdafx.h"
#include "Enemy.h"
#include "Inputs.h"
#include "game.h"
#include "ContentManager.h"

Enemy::Enemy()
    :isDead(false)
{

}
Enemy::Enemy(const Enemy& src)
    : AnimatedGameObject(src)
    , isDead(src.isDead)
{
    init(*contentManager);

    setPosition(src.getPosition());
    if (src.isActive())
        activate();
    else
        deactivate();
}
bool Enemy::init(const ContentManager& contentManager)
{
    isDead = false;

    currentState = State::STANDARD_ENEMY;
    addAnimation<State::STANDARD_ENEMY,EnemyIdleAnimation>(contentManager);
    addAnimation<State::EXPLODING, EnemyExplosionAnimation>(contentManager);

    return AnimatedGameObject::init(contentManager);
}

bool Enemy::update(float deltaT, const Inputs& inputs)
{
    if (isDead)
        if (!isExploding) {
            isExploding = true;
            explosionTimer.restart();
        }

    if (isExploding && explosionTimer.getElapsedTime().asSeconds() >= 1.0f) {
        respawnTimer.restart();
        return true;
    }
    move(sf::Vector2f(0, 5));

    if (getPosition().y > Game::GAME_HEIGHT)
        setPosition(sf::Vector2f(getPosition().x, 0.0f));

    return AnimatedGameObject::update(deltaT, inputs);
}

void Enemy::onHit()
{
    isDead = true;
    currentState = State::EXPLODING;
}