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
    window.draw(menuImage);
}

bool GameScene::init()
{
    /*if (titleContentManager.loadContent() == false)
    {
        return false;
    }*/
    menuImage.setTexture(menuImageTexture);
    menuImage.setOrigin(menuImage.getTexture()->getSize().x / 2.0f, menuImage.getTexture()->getSize().y / 2.0f);
    menuImage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 2.0f);
    /*instructions.setFont(titleContentManager.getFont());
    instructions.setString("Press any key to start");
    instructions.setCharacterSize(30);
    instructions.setPosition(Game::GAME_WIDTH / 2.0f - instructions.getGlobalBounds().width / 2.0f,
        Game::GAME_HEIGHT / 2 + (menuImage.getGlobalBounds().height / 2.0f) + 20);*/
    //gameMusic.setBuffer(titleContentManager.getGameMusicSoundBuffer());
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