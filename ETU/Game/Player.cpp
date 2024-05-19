#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include "game.h"
#include "ShipAnimation.h"
#include "Event.h"
#include "Publisher.h"

const float Player::SPEED = 2.0f;
const unsigned int Player::NB_INITIAL_LIVES = 3000;
const float Player::PLAYER_INVINCIBILITY_DURATION = 1.0f;
const sf::Color Player::RESET_COLOR = sf::Color::White;

Player::Player()
    : nbOfLives(NB_INITIAL_LIVES)
    , isInvincible(false)
    , nbOfBonusPts(0)
    , invincibilityTimer(0)
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
    updateTimeBeforeRevive(deltaT);
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

void Player::reduceLifePts()
{
    if (!getHasBonus() && nbOfLives > 0 && !isInvincible) {
        nbOfLives--;
        isInvincible = true;
        invincibilityTimer = 0;
        Publisher::notifySubscribers(Event::HEALTH_PTS_UPDATED, this);
    }
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
    nbOfLives+=100;
    Publisher::notifySubscribers(Event::HEALTH_PICKED_UP, this);
    Publisher::notifySubscribers(Event::HEALTH_PTS_UPDATED, this);
}

void Player::pickUpGunBonus()
{
    activateBonus();
    Publisher::notifySubscribers(Event::GUN_PICKED_UP, this);
    Publisher::notifySubscribers(Event::GUN_PTS_UPDATED, this);
}

void Player::reduceBonusPts()
{
    if (nbOfBonusPts >= 10 && !isInvincible) {
        nbOfBonusPts -= 10;
        Publisher::notifySubscribers(Event::GUN_PTS_UPDATED, this);
    }
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

void Player::updateTimeBeforeRevive(float elapsedTime) {
    if (isInvincible) {
        invincibilityTimer += elapsedTime;
        if (invincibilityTimer >= PLAYER_INVINCIBILITY_DURATION) {
            revive();
        }
        else {
            float transparency = invincibilityTimer / PLAYER_INVINCIBILITY_DURATION * 255;
            sf::Color color = RESET_COLOR;
            color.a = transparency;
            setColor(color);
        }
    }
}

void Player::revive() {
    if (isInvincible) {
        isInvincible = false;
    }
}