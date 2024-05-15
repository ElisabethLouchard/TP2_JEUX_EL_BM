#include "stdafx.h"
#include "GameScene.h"
#include "game.h"
#include "GameContentManager.h"

const float GameScene::TIME_BETWEEN_FIRE = 0.5f;
const float GameScene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const unsigned int GameScene::NB_BULLETS = 15;
const unsigned int GameScene::MAX_RECOIL = 25; // 0.5s

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
    recoil = std::max(0, recoil - 1);

    for (Bullet& b : playerBullets)
    {
        if (b.update(TIME_PER_FRAME)) {
            b.deactivate();
        }
    }

    for (Bullet& b : enemyBullets)
    {
        if (b.update(TIME_PER_FRAME)) {
            b.deactivate();
        }
    }

    player.update(TIME_PER_FRAME, inputs);

    if (inputs.fireBullet && recoil == 0)
    {
        fireBullet(player, false);
    }

    timeSinceLastFire += TIME_PER_FRAME;

    //for (Bullet& b : bullets)
    //{
    //    for (LargeEnemy& e : enemies)
    //    {
    //        if (b.collidesWith(e))
    //        {
    //            b.deactivate();
    //            e.onHit();
    //        }
    //    }
    //}

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
    for (const Bullet& b : playerBullets)
        b.draw(window);

    for (const Bullet& b : enemyBullets)
        b.draw(window);
    player.draw(window);
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
    
    initializeBulletPool(playerBullets, gameContentManager.getShipAnimationTexture(), false);
    initializeBulletPool(enemyBullets, gameContentManager.getShipAnimationTexture(), true);
    
    hud.initialize(gameContentManager);

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

void GameScene::fireBullet(const GameObject& object, bool isEnemy)
{
    Bullet& b1 = getAvailableObject(playerBullets);
    Bullet& b2 = getAvailableObject(playerBullets);
    if (isEnemy) {
        b1 = getAvailableObject(enemyBullets);
        b2 = getAvailableObject(enemyBullets);
    }

    b1.setPosition(sf::Vector2f(object.getPosition().x - object.getGlobalBounds().width / 3, object.getPosition().y));
    b2.setPosition(sf::Vector2f(object.getPosition().x + object.getGlobalBounds().width / 3, object.getPosition().y));
    if (!isEnemy) {
        inputs.fireBullet = false;
        recoil = MAX_RECOIL;
    }
}

void GameScene::initializeBulletPool(std::list<Bullet>& bulletPool, const sf::Texture& texture, const bool isEnemy) {
    // TODO : DRY
    for (int i = 0; i < NB_BULLETS; i++) {
        Bullet newBullet;
        if (isEnemy) {
            newBullet.initialize(texture, sf::Vector2f(0, 0), gameContentManager.getEnemyBulletSoundBuffer(), isEnemy);
        }
        else {
            newBullet.initialize(texture, sf::Vector2f(0, 0), gameContentManager.getPlayerBulletSoundBuffer(), isEnemy);
        }
        bulletPool.push_back(newBullet);
    }
}

template<typename GameObject>
GameObject& GameScene::getAvailableObject(std::list<GameObject>& objects)
{
    for (GameObject& obj : objects)
    {
        if (!obj.isActive())
        {
            obj.activate();
            return obj;
        }
    }

    return objects.back();
}