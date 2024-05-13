#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include "game.h"
#include "ShipAnimation.h"

const float Player::SPEED = 2.0f;

Player::Player()
{

}

bool Player::init(const ContentManager& contentManager)
{
    setScale(3, 3);
    setPosition(sf::Vector2f(Game::GAME_WIDTH * 0.5f, Game::GAME_HEIGHT - 200)); // TODO : Changer la position en Y (+dynamique)
    activate();

    currentState = State::SHIP;
    addAnimation<State::SHIP, ShipAnimation>(contentManager);

    return AnimatedGameObject::init(contentManager);
}

bool Player::update(float deltaT, const Inputs& inputs)
{
    move(sf::Vector2f(-inputs.moveFactorX * SPEED, -inputs.moveFactorY * SPEED));
    return AnimatedGameObject::update(deltaT, inputs);
}