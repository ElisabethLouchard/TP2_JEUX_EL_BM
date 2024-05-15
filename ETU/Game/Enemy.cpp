#include "stdafx.h"
#include "Enemy.h"
#include "Inputs.h"
#include "game.h"
#include "ContentManager.h"
#include "EnemyIdleAnimation.h"

const int MAX_NB_OF_HITS = 5;

Enemy::Enemy()
    :isDead(false)
{

}
Enemy::Enemy(const Enemy& src)
    : AnimatedGameObject(src)
    , isDead(src.isDead)
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
    setScale(0.75, 0.75);
    isDead = false;

    activate();

    currentState = State::STANDARD_ENEMY;
    addAnimation<State::STANDARD_ENEMY,EnemyIdleAnimation>(contentManager);
    addAnimation<State::EXPLODING, EnemyExplosionAnimation>(contentManager);

    return AnimatedGameObject::init(contentManager);
}

bool Enemy::update(float deltaT, const Inputs& inputs)
{
    if (isDead)
        if (!isExploding) {
            isExploding = true;
            explosionTimer.restart();
        }
    
    if (nbOfHit == MAX_NB_OF_HITS)
        onDying();

    if (isExploding && explosionTimer.getElapsedTime().asSeconds() >= 1.0f) {
        respawnTimer.restart();
        return true;
    }
    move(sf::Vector2f(0, 5));

    if (getPosition().y > Game::GAME_HEIGHT)
        setPosition(sf::Vector2f(getPosition().x, 0.0f));


    return AnimatedGameObject::update(deltaT, inputs);
}

void Enemy::onHit()
{
    nbOfHit++;
}

void Enemy::onDying()
{
    isDead = true;
    currentState = State::EXPLODING;
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

bool Enemy::isAlive() 
{
    return !isDead;
}
