#include "stdafx.h"
#include "Bullet.h"
#include "ContentManager.h"
#include "GameContentManager.h"
#include "game.h"

const float Bullet::BULLET_SPEED = 600;
const unsigned long long Bullet::TIME_TO_LIVE = 2000;

Bullet::Bullet(const sf::Vector2f& initialPosition, const sf::Vector2f& initialThrust)
    : GameObject()
{
    setPosition(initialPosition);
    move(initialThrust);
}

Bullet::Bullet(const Bullet& src)
    :GameObject(src)
{

}

bool Bullet::update(float elapsedTime)
{
    move(sf::Vector2f(0, -BULLET_SPEED * elapsedTime));
    if (getPosition().y > Game::GAME_HEIGHT)
        return true;
    return false;
}

bool Bullet::init(const ContentManager& contentManager)
{
    const GameContentManager& gameContentManager = (const GameContentManager&)contentManager;
    GameObject::init(gameContentManager);
    setTexture(gameContentManager.getShipAnimationTexture());
    setTextureRect(sf::IntRect(264, 106, 16, 5));
    setScale(2,2);
    setRotation(90); 
    return true;
}

