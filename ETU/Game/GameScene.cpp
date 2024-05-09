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
    hud.draw(window);
}

bool GameScene::init()
{
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
    sf::Event event;
    while (window.pollEvent(event))
    {
        //x sur la fenêtre
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
        {
            window.close();
            retval = true;
        }
        if (event.type == sf::Event::KeyPressed) {

            hasTransition = true;
        }
    }
    return retval;

}