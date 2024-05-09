#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include "game.h"
#include "ShipAnimation.h"

Player::Player()
{

}

bool Player::init(const ContentManager& contentManager)
{
    activate();
    setPosition(sf::Vector2f(Game::GAME_WIDTH * 0.5f, 100.0f));

    currentState = State::SHIP;
    addAnimation<State::SHIP, ShipAnimation>(contentManager);

    return AnimatedGameObject::init(contentManager);
}

bool Player::update(float deltaT, const Inputs& inputs)
{
    move(sf::Vector2f(-inputs.moveFactorX, -inputs.moveFactorY));
    return AnimatedGameObject::update(deltaT, inputs);
}