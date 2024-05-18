#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include "game.h"
#include "ShipAnimation.h"
#include "Event.h"
#include "Publisher.h"

const float Player::SPEED = 2.0f;

Player::Player()
{

}

bool Player::init(const ContentManager& contentManager)
{
    setScale(3, 3);
    setPosition(sf::Vector2f(Game::GAME_WIDTH * 0.5f, Game::GAME_HEIGHT - Game::HUD_HEIGHT));
    activate();

    currentState = State::SHIP;
    addAnimation<State::SHIP, ShipAnimation>(contentManager);

    return AnimatedGameObject::init(contentManager);
}

bool Player::update(float deltaT, const Inputs& inputs)
{
    move(sf::Vector2f(-inputs.moveFactorX * SPEED, -inputs.moveFactorY * SPEED));
    adjustCrossingViewLimits();
    return AnimatedGameObject::update(deltaT, inputs);
}

void Player::adjustCrossingViewLimits()
{
    sf::Vector2f position = getPosition();
    position.x = std::max(getGlobalBounds().width / 2.0f, std::min(position.x, Game::GAME_WIDTH - getGlobalBounds().width / 2.0f));
    position.y = std::max(getGlobalBounds().height / 2.0f, std::min(position.y, (Game::GAME_HEIGHT - Game::HUD_HEIGHT) - getGlobalBounds().height / 2.0f));
    setPosition(position);
}

void Player::kill()
{
    nbOfLives = 0;
    deactivate();
}

bool Player::isAlive() const
{
    return nbOfLives != 0;
}

bool Player::getHasBonus() const
{
    return nbOfBonusPts > 0;
}

void Player::pickUpHealthBonus()
{
    nbOfLives++;
    Publisher::notifySubscribers(Event::HEALTH_PICKED_UP, this);
}

void Player::pickUpGunBonus()
{
    activateBonus();
    Publisher::notifySubscribers(Event::GUN_PICKED_UP, this);
}

void Player::deactivateBonus()
{
    nbOfBonusPts = 0;
}

void Player::activateBonus()
{
    nbOfBonusPts = 100;
}

unsigned int Player::getNbOfLives() const
{
    return nbOfLives;
}

unsigned int Player::getNbOfBonusPts() const
{
    return nbOfBonusPts;
}