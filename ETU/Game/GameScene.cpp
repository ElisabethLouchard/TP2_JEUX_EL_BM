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
    
    for (Enemy& e : enemies)
        if (e.update(1.0f / (float)Game::FRAME_RATE, inputs))
            e.deactivate();
    
    if (hasTransition)
    {
        pause();
        return SceneType::SCORE_SCENE;
    }

    enemies.remove_if([](const GameObject& b) {return !b.isActive(); });
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

    for (int i = 0; i < 10; i++)
    {
        Enemy enemy;
        enemy.init(gameContentManager);
        enemy.setPosition(sf::Vector2f((float)Game::GAME_WIDTH + 50.0f * (float)(rand() % 100), i * (float)Game::GAME_HEIGHT / 10.0f));
        enemy.activate();
        enemies.push_back(enemy);
    }
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