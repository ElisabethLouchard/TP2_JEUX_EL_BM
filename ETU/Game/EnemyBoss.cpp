#include "stdafx.h"
#include "EnemyBoss.h"
#include "ContentManager.h"
#include "EnemyBossIdleAnimation.h"
#include "game.h"

const float MOVE_SPEED_X = 900.0f;
const float MOVE_SPEED_Y = 5.0f;

EnemyBoss::EnemyBoss()
    : Enemy()
{
}

EnemyBoss::EnemyBoss(const EnemyBoss& src)
    : Enemy(src)
{
}

bool EnemyBoss::init(const ContentManager& contentManager)
{
    setPosition(Game::GAME_WIDTH / 2, 0.0f);
    currentState = State::BOSS;
    addAnimation<State::BOSS, EnemyBossIdleAnimation>(contentManager);
    addAnimation<State::EXPLODING, EnemyExplosionAnimation>(contentManager);

    return Enemy::init(contentManager);
}

bool EnemyBoss::update(float deltaT, const Inputs& inputs)
{
    move(cos(moveAngle) * deltaT * MOVE_SPEED_X, sin(moveAngle) * deltaT * 5.0f);
    return Enemy::update(deltaT, inputs);
}

void EnemyBoss::onHit()
{
    Enemy::onHit();
    currentState = State::EXPLODING;
}

void EnemyBoss::onDying()
{
    Enemy::onDying();
}

void EnemyBoss::setDestination(const sf::Vector2f& dest)
{
    moveAngle = atan2f((dest.y - getPosition().y), (dest.x - getPosition().x));
}