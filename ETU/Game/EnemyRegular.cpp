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

    return returnValue;
}

bool EnemyRegular::update(float deltaT, const Inputs& inputs)
{
    if (isDead)
        if (!isExploding) {
            isExploding = true;
            explosionTimer.restart();
        }

    if (nbOfHit == 5)
        onDying();

    if (isExploding && explosionTimer.getElapsedTime().asSeconds() >= 1.0f) {
        respawnTimer.restart();
        return true;
    }
    move(sf::Vector2f(0, 5));

    if (getPosition().y > Game::GAME_HEIGHT)
        setPosition(sf::Vector2f(getPosition().x, 0.0f));


    return Enemy::update(deltaT, inputs);
}

void EnemyRegular::onHit()
{
    Enemy::onHit();
}

void EnemyRegular::onDying()
{
    Enemy::onDying();
}