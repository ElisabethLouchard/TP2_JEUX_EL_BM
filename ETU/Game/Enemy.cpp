#include "stdafx.h"
#include "Enemy.h"
#include "Inputs.h"
#include "game.h"
#include "ContentManager.h"
#include "EnemyIdleAnimation.h"

const short Enemy::MAX_NB_OF_HITS = 1;

Enemy::Enemy()
    : isDead(false)
    , nbOfHit(0)
{

}
Enemy::Enemy(const Enemy& src)
    : AnimatedGameObject(src)
    , isDead(src.isDead)
    , nbOfHit(src.nbOfHit)
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
    addAnimation<State::STANDARD_ENEMY, EnemyIdleAnimation>(contentManager);
    activate();

    return AnimatedGameObject::init(contentManager);
}

bool Enemy::update(float deltaT, const Inputs& inputs)
{
    return AnimatedGameObject::update(deltaT, inputs);
}

void Enemy::onHit()
{
    nbOfHit++;
    if (nbOfHit >= MAX_NB_OF_HITS)
        onDying();
}

void Enemy::onDying()
{
    isDead = true;
    speak();
    deactivate();
}

void Enemy::loadEnemySound(const sf::SoundBuffer& soundbuffer)
{
    enemyKilledSound.setBuffer(soundbuffer);
}

void Enemy::speak()
{
    enemyKilledSound.play();
}

bool Enemy::isAlive() const
{
    return !isDead;
}
