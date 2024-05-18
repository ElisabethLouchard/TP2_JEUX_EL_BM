#include "stdafx.h"
#include "GameScene.h"
#include "game.h"
#include "GameContentManager.h"
#include "random.h"

const float GameScene::TIME_BETWEEN_FIRE = 0.5f;
const float spawnInterval = 0.01f;
const float BONUS_SPAWN_CHANCE = 0.5f;
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
	static int cptScrollBackground = 0;
	gameBackground.setTextureRect(sf::IntRect(0, (int)(0.5f * cptScrollBackground--), Game::GAME_WIDTH, Game::GAME_HEIGHT));
	SceneType retval = getSceneType();
	recoil = std::max(0, recoil - 1);
	player.update(TIME_PER_FRAME, inputs);
	boss.setDestination(player.getPosition());
	boss.update(TIME_PER_FRAME, inputs);

	if (boss.getShouldFireBullet())
	{
		fireBullet(boss, true);
	}

	/*for (EnemyRegular& e : enemies)
	{
		if (e.update(TIME_PER_FRAME, inputs))
			e.deactivate();
	}*/

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

    if (inputs.fireBullet && recoil == 0)
    {
        fireBullet(player, false);
    }

    timeSinceLastFire += TIME_PER_FRAME;

	for (EnemyRegular& e : enemies)
	{
		for (Bullet& b : playerBullets)
		{
			if (b.collidesWith(e))
			{
				b.deactivate();
				e.onHit();
				if (!e.isAlive())
				{
					spawnBonus(e.getPosition());
				}
			}
		}
		if (player.collidesWith(e))
		{
			spawnBonus(e.getPosition());
			e.onDying();
		}
	}

	for (Bullet& b : enemyBullets)
	{
		if (b.collidesWith(player))
		{
			player.deactivateBonus();
		}
	}

	for(LifeBonus& b : listLifeBonus)
	{
		if (b.isActive())
		{
			b.update(TIME_PER_FRAME);
			if (b.collidesWith(player))
			{
				hud.updateNbOfLiveText(nbOfLives += 1);
				hud.updateScoreText(score += 10);
				b.deactivate();
			}
		}
	}

	for (WeaponBonus& b : listWeaponBonus)
	{
		if (b.isActive())
		{
			b.update(TIME_PER_FRAME);
			if (b.collidesWith(player))
			{
				hud.updateScoreText(score += 10);
				hud.updateBonusText(50);
				player.activateBonus();
				b.deactivate();
			}
		}
	}

	timeSinceLastFire += TIME_PER_FRAME;

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
	for (const LifeBonus& b : listLifeBonus)
		b.draw(window);
	for (const WeaponBonus& b : listWeaponBonus)
		b.draw(window);
	for (const EnemyRegular& e : enemies)
		e.draw(window);
	boss.draw(window);

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
	for (int i = 0; i < 20; i++)
	{
		EnemyRegular enemy;
		enemy.init(gameContentManager);
		enemy.setPosition(sf::Vector2f(i * (float)Game::GAME_WIDTH / 10.0f, -50.0f * (float)(rand() % 100)));
		enemies.push_back(enemy);
		enemy.loadEnemySound(gameContentManager.getEnemyKilledSoundBuffer());
	}

	boss.init(gameContentManager);

	for (int i = 0; i < 10; i++)
	{
		LifeBonus lifeBonus;
		const sf::Vector2f& initialPosition = sf::Vector2f(0, 0);
		lifeBonus.initialize(gameContentManager.getBonusTexture(), initialPosition, gameContentManager.getLifeBonusSoundBuffer());
		listLifeBonus.push_back(lifeBonus);
	}

	for (int i = 0; i < 10; i++)
	{
		WeaponBonus weaponBonus;
		const sf::Vector2f& initialPosition = sf::Vector2f(0, 0);
		weaponBonus.initialize(gameContentManager.getBonusTexture(), initialPosition, gameContentManager.getWeaponBonusSoundBuffer());
		listWeaponBonus.push_back(weaponBonus);
	}

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
	if (isEnemy) {
		Bullet& b1 = getAvailableObject(enemyBullets);
		Bullet& b2 = getAvailableObject(enemyBullets);
		b1.setPosition(sf::Vector2f(object.getPosition().x - object.getGlobalBounds().width / 3, object.getPosition().y));
		b2.setPosition(sf::Vector2f(object.getPosition().x + object.getGlobalBounds().width / 3, object.getPosition().y));
	}
	else {
		Bullet& b1 = getAvailableObject(playerBullets);
		Bullet& b2 = getAvailableObject(playerBullets);
		b1.setPosition(sf::Vector2f(object.getPosition().x - object.getGlobalBounds().width / 3, object.getPosition().y));
		b2.setPosition(sf::Vector2f(object.getPosition().x + object.getGlobalBounds().width / 3, object.getPosition().y));
		if (player.getHasBonus()) {
			Bullet& b3 = getAvailableObject(playerBullets);
			b3.setPosition(object.getPosition());
		}
		inputs.fireBullet = false;
		recoil = MAX_RECOIL;
	}
}

void GameScene::spawnBonus(const sf::Vector2f& enemyPosition)
{
	Random randomGenerator;

	double randomValue = randomGenerator.nextDouble();

	double randomBonus = randomGenerator.nextDouble();

	if (randomValue <= BONUS_SPAWN_CHANCE)
	{
		if (randomBonus < 0.5) {
			Bonus& b = getAvailableObject(listLifeBonus);
			b.setPosition(enemyPosition);
		}
		else
		{
			Bonus& b = getAvailableObject(listWeaponBonus);
			b.setPosition(enemyPosition);
		}
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