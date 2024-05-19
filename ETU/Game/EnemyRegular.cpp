#include "stdafx.h"
#include "EnemyRegular.h"
#include "ContentManager.h"
#include "EnemyIdleAnimation.h"
#include "game.h"

EnemyRegular::EnemyRegular()
    : Enemy()
{
}

EnemyRegular::EnemyRegular(const EnemyRegular& src)
    : Enemy(src)
{
}

bool EnemyRegular::init(const ContentManager& contentManager)
{
    bool returnValue = Enemy::init(contentManager);
    setScale(1, 0.5);
    
    return returnValue;
}

bool EnemyRegular::update(float deltaT, const Inputs& inputs)
{
    bool returnValue = Enemy::update(deltaT, inputs);

    move(sf::Vector2f(0, 5));

    if (getPosition().y > Game::GAME_HEIGHT)
        setPosition(sf::Vector2f(getPosition().x, 0.0f));
    
    shouldFireBullets = false;
    if (animations[State::STANDARD_ENEMY]->getPercentage() == 0.5 && getPosition().y > 0) {
        shouldFireBullets = true;
    }
    return returnValue;
}

void EnemyRegular::onHit()
{
    Enemy::onHit();
}

void EnemyRegular::onDying()
{
    Enemy::onDying();
}