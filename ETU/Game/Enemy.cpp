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
    setPosition(sf::Vector2f(0.0f, Game::GAME_HEIGHT * 0.5f));


    currentState = State::STANDARD_ENEMY;
    addAnimation<State::EXPLODING, EnemyExplosionAnimation>(contentManager);

    return AnimatedGameObject::init(contentManager);
}

bool Enemy::update(float deltaT, const Inputs& inputs)
{
    move(sf::Vector2f(-5, 0));

    return AnimatedGameObject::update(deltaT, inputs);
}

void Enemy::onHit()
{
    isDead = true;
    currentState = State::EXPLODING;
}