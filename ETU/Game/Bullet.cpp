#include "stdafx.h"
#include "Bullet.h"
#include "ContentManager.h"
#include "GameContentManager.h"
#include "game.h"

const float Bullet::BULLET_SPEED = 1000;

Bullet::Bullet(const sf::Vector2f& initialPosition, const sf::Vector2f& initialThrust)
    : GameObject()
    ,isEnemy(false)
{
    setPosition(initialPosition);
    move(initialThrust);
}

Bullet::Bullet(const Bullet& src)
    :GameObject(src)
    ,shotSound(src.shotSound)
    ,isEnemy(src.isEnemy)
{

}

Bullet& Bullet::operator=(const Bullet& rhs)
{
    if (this != &rhs)
    {
        GameObject::operator=(rhs);
        GameObject::initialize(*rhs.getTexture(), rhs.getPosition());
        shotSound = rhs.shotSound;
        isEnemy = rhs.isEnemy;
    }
    return *this;
}

bool Bullet::update(float elapsedTime)
{
    if (isEnemy) {
        move(sf::Vector2f(0, BULLET_SPEED * elapsedTime));
        if (getPosition().y > Game::GAME_HEIGHT)
            return true;
    }
    else {
        move(sf::Vector2f(0, -BULLET_SPEED * elapsedTime));
        if (getPosition().y < 0)
            return true;
    }
    return false;
}

void Bullet::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb, const bool isEnemy)
{
    this->isEnemy = isEnemy;
    setScale(2, 2);
    GameObject::initialize(texture, initialPosition);
    setTextureRect(sf::IntRect(264, 106, 16, 5));
    setRotation(90);
    if (isEnemy) {
        setRotation(-90);
        setTextureRect(sf::IntRect(287, 106, 16, 5));
    }

    shotSound.setBuffer(sb);
}

void Bullet::draw(sf::RenderWindow& window) const
{
    if (isActive())
        window.draw(*this);
}


void Bullet::activate()
{
    GameObject::activate();
}

void Bullet::playSound()
{
    shotSound.play();
}