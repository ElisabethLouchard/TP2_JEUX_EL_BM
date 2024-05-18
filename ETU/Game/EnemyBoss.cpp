#include "stdafx.h"
#include "EnemyBoss.h"
#include "ContentManager.h"
#include "EnemyBossIdleAnimation.h"
#include "game.h"

const float MOVE_SPEED_X = 900.0f;
const float MOVE_SPEED_Y = 5.0f;

EnemyBoss::EnemyBoss()
    : Enemy()
    , moveAngle(0)
{
}

EnemyBoss::EnemyBoss(const EnemyBoss& src)
    : Enemy(src)
    , moveAngle(src.moveAngle)
{
}

bool EnemyBoss::init(const ContentManager& contentManager)
{
    bool returnValue = Enemy::init(contentManager);
    currentState = State::BOSS;
    addAnimation<State::BOSS, EnemyBossIdleAnimation>(contentManager);

    return returnValue;
}

bool EnemyBoss::update(float deltaT, const Inputs& inputs)
{
    move(cos(moveAngle) * deltaT * MOVE_SPEED_X, sin(moveAngle) * deltaT * 5.0f);
    shouldFireBullets = false;
    if (animations[State::BOSS]->getPercentage() == 0.5) {
        shouldFireBullets = true;
    }
    return Enemy::update(deltaT, inputs);
}

void EnemyBoss::onHit()
{
    Enemy::onHit();
    currentState = State::EXPLODING;
}

void EnemyBoss::kill()
{
    Enemy::kill();
}

void EnemyBoss::setDestination(const sf::Vector2f& dest)
{
    moveAngle = atan2f((dest.y - getPosition().y), (dest.x - getPosition().x));
}

bool EnemyBoss::getShouldFireBullet() const 
{
    return shouldFireBullets;
}