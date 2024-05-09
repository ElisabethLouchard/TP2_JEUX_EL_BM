#include "stdafx.h"
#include "GameScene.h"

#include "game.h"

GameScene::GameScene()
    : Scene(SceneType::GAME_SCENE)
{

}

GameScene::~GameScene()
{

}
SceneType GameScene::update()
{
    SceneType retval = getSceneType();
    player.update(1.0f / (float)Game::FRAME_RATE, inputs);
    if (hasTransition)
    {
        pause();
        return SceneType::SCORE_SCENE;
    }

    return retval;
}

void GameScene::draw(sf::RenderWindow& window) const
{
    window.draw(gameBackground);
}

bool GameScene::init()
{
    inputs.reset();
    if (gameContentManager.loadContent() == false)
    {
        return false;
    }
    gameBackground.setTexture(gameContentManager.getBackgroundTexture());
    gameBackground.setOrigin(gameBackground.getTexture()->getSize().x / 2.0f, gameBackground.getTexture()->getSize().y / 2.0f);
    gameBackground.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 2.0f);
    hud.initialize(gameContentManager);
    return true;
}

bool GameScene::uninit()
{
    return true;
}

bool GameScene::handleEvents(sf::RenderWindow& window)
{
    bool retval = false;
    inputs.reset();
    sf::Event event;
    while (window.pollEvent(event))
    {
        //x sur la fenêtre
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
        {
            window.close();
            retval = true;
        }
    }
    inputs.moveFactorY += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ? 3.0f : 0.0f;
    inputs.moveFactorY += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ? -3.0f : 0.0f;
    inputs.moveFactorX += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ? 3.0f : 0.0f;
    inputs.moveFactorX += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ? -3.0f : 0.0f;
    return retval;

}