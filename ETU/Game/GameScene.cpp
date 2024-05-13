#include "stdafx.h"
#include "GameScene.h"
#include "game.h"
#include "GameContentManager.h"

const float GameScene::TIME_BETWEEN_FIRE = 0.5f;
const float spawnInterval = 0.01f;

GameScene::GameScene()
    : Scene(SceneType::GAME_SCENE)
{

}

GameScene::~GameScene()
{

}
SceneType GameScene::update()
{
    static int cptScrollBackground = 0;
    gameBackground.setTextureRect(sf::IntRect(0, (int)(0.5f * cptScrollBackground--), Game::GAME_WIDTH, Game::GAME_HEIGHT));
    SceneType retval = getSceneType();
    player.update(1.0f / (float)Game::FRAME_RATE, inputs);
    for (Bullet& b : bullets)
    {
        if (b.update(1.0f / (float)Game::FRAME_RATE))
            b.deactivate();
    }

    for (Enemy& e : enemies)
    {
        if (e.update(1.0f / (float)Game::FRAME_RATE, inputs))
            e.deactivate();
    }

    if (inputs.fireBullet && timeSinceLastFire >= TIME_BETWEEN_FIRE)
    {
        fireBullet(player.getPosition());
    }

    bullets.remove_if([](const GameObject& b) {return !b.isActive(); });
    enemies.remove_if([](const GameObject& b) {return !b.isActive(); });
    timeSinceLastFire += 1.0f / (float)Game::FRAME_RATE;
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
    for (const Bullet& b : bullets)
        b.draw(window);
    player.draw(window);
    for (const Enemy& e : enemies)
        e.draw(window);
    hud.draw(window);
}

bool GameScene::init()
{
    inputs.reset();
    if (gameContentManager.loadContent() == false)
    {
        return false;
    }
    gameBackground.setTexture(gameContentManager.getBackgroundTexture());
    hud.initialize(gameContentManager);
    for (int i = 0; i < 10; i++)
    {
        Enemy enemy;
        enemy.init(gameContentManager);
        enemy.setPosition(sf::Vector2f((float)(rand() % Game::GAME_WIDTH), (float)(rand() % -1000)));
        enemy.activate();
        enemies.push_back(enemy);
    }
    return player.init(gameContentManager);
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
    inputs.fireBullet = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    return retval;
}

void GameScene::fireBullet(const sf::Vector2f& position)
{
    Bullet newBullet1;
    newBullet1.init(gameContentManager);
    newBullet1.setPosition(sf::Vector2f(position.x + player.getGlobalBounds().width / 3, position.y));
    newBullet1.activate();
    bullets.push_back(newBullet1);

    Bullet newBullet2;
    newBullet2.init(gameContentManager);
    newBullet2.setPosition(sf::Vector2f(position.x - player.getGlobalBounds().width / 3, position.y));
    newBullet2.activate();
    bullets.push_back(newBullet2);
    timeSinceLastFire = 0;
}