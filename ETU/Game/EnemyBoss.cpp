#include "stdafx.h"
#include "EnemyBoss.h"
#include "ContentManager.h"

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
    if (!Enemy::init(contentManager))
        return false;

    return true;
}

bool EnemyBoss::update(float deltaT, const Inputs& inputs)
{
    if (!Enemy::update(deltaT, inputs))
        return false;

    return true;
}

void EnemyBoss::onHit()
{
    Enemy::onHit();
}

void EnemyBoss::onDying()
{
    Enemy::onDying();
}