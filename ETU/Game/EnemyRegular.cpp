#include "stdafx.h"
#include "EnemyRegular.h"
#include "ContentManager.h"
#include "EnemyIdleAnimation.h"
#include "game.h"

const float EnemyRegular::MOVE_SPEED_Y = 5.0f;

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

    move(sf::Vector2f(0, MOVE_SPEED_Y));

    if (getPosition().y > Game::GAME_HEIGHT)
        setPosition(sf::Vector2f(getPosition().x, 0.0f));
    
    shouldFireBullets = false;
    // 0.5f = 50% = � la moiti� de l'animation
    if (animations[State::STANDARD_ENEMY]->getPercentage() == 0.5f && getPosition().y > 0) {
        shouldFireBullets = true;
    }
    return returnValue;
}