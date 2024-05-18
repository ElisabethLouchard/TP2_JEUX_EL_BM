#include "stdafx.h"
#include "Enemy.h"
#include "Inputs.h"
#include "game.h"
#include "ContentManager.h"
#include "GameContentManager.h"
#include "EnemyIdleAnimation.h"
#include "Publisher.h"

const short Enemy::MAX_NB_OF_HITS = 5;

Enemy::Enemy()
    : nbOfHit(0)
    , shouldFireBullets(false)
{
}
Enemy::Enemy(const Enemy& src)
    : AnimatedGameObject(src)
    , nbOfHit(src.nbOfHit)
    , shouldFireBullets(src.shouldFireBullets)
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
    const GameContentManager& gameContentManager = (const GameContentManager&)contentManager;
    const sf::SoundBuffer& sb = gameContentManager.getEnemyKilledSoundBuffer();
    enemyKilledSound.setBuffer(sb);

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
        kill();
}

void Enemy::kill()
{
    speak();
    Publisher::notifySubscribers(Event::ENEMY_KILLED, this);
    deactivate();
}

void Enemy::speak()
{
    enemyKilledSound.play();
}

bool Enemy::getShouldFireBullet() const
{
    return shouldFireBullets;
}
