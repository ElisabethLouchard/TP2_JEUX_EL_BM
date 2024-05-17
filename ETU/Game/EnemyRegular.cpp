#include "stdafx.h"
#include "EnemyRegular.h"
#include "ContentManager.h"

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
    if (!Enemy::init(contentManager))
        return false;

    return true;
}

bool EnemyRegular::update(float deltaT, const Inputs& inputs)
{
    if (!Enemy::update(deltaT, inputs))
        return false;

    return true;
}

void EnemyRegular::onHit()
{
    Enemy::onHit();
}

void EnemyRegular::onDying()
{
    Enemy::onDying();
}