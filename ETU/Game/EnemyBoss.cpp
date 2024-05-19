#include "stdafx.h"
#include "EnemyBoss.h"
#include "ContentManager.h"
#include "EnemyBossIdleAnimation.h"
#include "game.h"

const float MOVE_SPEED_X = 900.0f;
const float MOVE_SPEED_Y = 20.0f;
const unsigned int NB_INITIAL_LIVES = 50;

EnemyBoss::EnemyBoss()
    : Enemy()
    , moveAngle(0)
    , currentHealth(NB_INITIAL_LIVES)
{
}

EnemyBoss::EnemyBoss(const EnemyBoss& src)
    : Enemy(src)
    , moveAngle(src.moveAngle)
    , currentHealth(src.currentHealth)
{
}

bool EnemyBoss::init(const ContentManager& contentManager)
{
    bool returnValue = Enemy::init(contentManager);
    currentState = State::BOSS;

    addAnimation<State::BOSS, EnemyBossIdleAnimation>(contentManager);

    healthBar.init(200, 20, currentHealth);
    healthBar.setPosition(getPosition().x, getPosition().y - 80);

    return returnValue;
}

bool EnemyBoss::update(float deltaT, const Inputs& inputs)
{
    bool returnValue = Enemy::update(deltaT, inputs);
    move(cos(moveAngle) * deltaT * MOVE_SPEED_X, sin(moveAngle) * deltaT * MOVE_SPEED_Y);
    shouldFireBullets = false;
    if (animations[State::BOSS]->getPercentage() == 0.5 && isActive()) {
        shouldFireBullets = true;
    }

    if (currentHealth == 0) {
        deactivate();
    }

    healthBar.setPosition(getPosition().x, getPosition().y - 80);
    return returnValue;
}

void EnemyBoss::draw(sf::RenderWindow& window) const 
{
    Enemy::draw(window);
    healthBar.draw(window);
}

void EnemyBoss::onHit()
{
    if (currentHealth > 0) {
        currentHealth--;
        healthBar.setCurrentValue(currentHealth);
    }
}

void EnemyBoss::activate() 
{
    Enemy::activate();
    healthBar.activate();
}

void EnemyBoss::setDestination(const sf::Vector2f& dest)
{
    moveAngle = atan2f((dest.y - getPosition().y), (dest.x - getPosition().x));
}