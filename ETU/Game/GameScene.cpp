#include "stdafx.h"
#include "GameScene.h"
#include "game.h"
#include "GameContentManager.h"
#include "random.h"
#include "Subscriber.h"
#include "Publisher.h"
#include <iostream>

const float GameScene::TIME_BETWEEN_FIRE = 0.5f;
const float GameScene::BONUS_SPAWN_CHANCE = 0.4f;
const float GameScene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const unsigned int GameScene::NB_BULLETS = 50;
const unsigned int GameScene::MAX_RECOIL = 15; // 0.3s
const unsigned int GameScene::NB_ENEMIES = 21;
const unsigned int GameScene::NB_BONUSES = 10;
const unsigned int GameScene::SCORE_GAIN_PTS = 50;
const unsigned int GameScene::REGULAR_ENEMY_DAMAGE = 10;
const unsigned int GameScene::BOSS_ENEMY_DAMAGE = 100;

SceneResult GameScene::scoreFinal;

GameScene::GameScene()
	: Scene(SceneType::GAME_SCENE)
	, timeSinceLastFire(0)
	, timeSinceLastSpawn(0)
	, nbOfEnemyDeaths(0)
	, score(0)
	, recoil(0)
	, hasScoreSceneBeenDisplayed(false)
{

}

GameScene::~GameScene()
{
}

SceneType GameScene::update()
{
	SceneType retval = getSceneType();

	static int cptScrollBackground = 0;
	gameBackground.setTextureRect(sf::IntRect(0, (int)(0.5f * cptScrollBackground--), Game::GAME_WIDTH, Game::GAME_HEIGHT));
	
	recoil = std::max(0, recoil - 1);
	
	player.update(TIME_PER_FRAME, inputs);

	if (boss.getShouldFireBullet())
	{
		fireBullet(boss, true);
	}

	for (EnemyRegular& e : enemies)
	{
		if (e.getShouldFireBullet() && e.isActive())
		{
			fireBullet(e, true);
		}
		if (e.update(TIME_PER_FRAME, inputs))
			e.deactivate();
	}

	for (Bullet& b : playerBullets)
	{
		if (b.collidesWith(boss))
		{
			boss.onHit();
			b.deactivate();
		}

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

	for (EnemyRegular& e : enemies)
	{
		for (Bullet& b : playerBullets)
		{
			if (b.collidesWith(e))
			{
				b.deactivate();
				e.onHit();
			}
		}

		if (player.collidesWith(e))
		{
			e.kill();
			player.reduceLifePts(REGULAR_ENEMY_DAMAGE);
		}
	}

	for (Bullet& b : enemyBullets)
	{
		if (b.collidesWith(player))
		{
			player.reduceBonusPts();
			if (nbOfEnemyDeaths == NB_ENEMIES) {
				player.reduceLifePts(BOSS_ENEMY_DAMAGE);
			}
			else {
				player.reduceLifePts(REGULAR_ENEMY_DAMAGE);
			}
			
		}
	}

	for (LifeBonus& b : listLifeBonus)
	{
		if (b.isActive())
		{
			b.update(TIME_PER_FRAME);
			if (b.collidesWith(player))
			{
				b.deactivate();
				player.pickUpHealthBonus();
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
				b.deactivate();
				player.pickUpGunBonus();
			}
		}
	}

	if (nbOfEnemyDeaths == NB_ENEMIES)
	{
		boss.setDestination(player.getPosition());
		boss.update(TIME_PER_FRAME, inputs);
	}

	if (boss.isActive() && boss.collidesWith(player))
	{
		player.kill();
	}

	timeSinceLastFire += TIME_PER_FRAME;

	if (hasScoreSceneBeenDisplayed) {
		return SceneType::NONE;
	}

	if (!player.isAlive() || !boss.isAlive()) {
			scoreFinal.gameSceneResult.score = score;
			hasScoreSceneBeenDisplayed = true;
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

	Publisher::addSubscriber(*this, Event::ENEMY_KILLED);
	Publisher::addSubscriber(*this, Event::HEALTH_PICKED_UP);
	Publisher::addSubscriber(*this, Event::GUN_PICKED_UP);

	gameBackground.setTexture(gameContentManager.getBackgroundTexture());
	hud.initialize(gameContentManager);

	srand(static_cast<unsigned int>(time(nullptr)));

	for (int i = 0; i < NB_ENEMIES; i++)
	{
		EnemyRegular enemy;
		enemy.init(gameContentManager);

		// Générer les positions aléatoires avec rand()
		float posX = static_cast<float>(rand() % Game::GAME_WIDTH);
		float posY = -50.0f * static_cast<float>(rand() % 100);

		enemy.setPosition(sf::Vector2f(posX, posY));
		enemies.push_back(enemy);
	}

	boss.init(gameContentManager);

	for (int i = 0; i < NB_BONUSES; i++)
	{
		LifeBonus lifeBonus;
		const sf::Vector2f& initialPosition = sf::Vector2f(0, 0);
		lifeBonus.initialize(gameContentManager.getBonusTexture(), initialPosition, gameContentManager.getLifeBonusSoundBuffer());
		listLifeBonus.push_back(lifeBonus);
	}

	for (int i = 0; i < NB_BONUSES; i++)
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

	if (sf::Joystick::isConnected(0)) {
		float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

		inputs.moveFactorX -= (std::abs(x) > 15) ? x / 100.0f * 3.0f : 0.0f;
		inputs.moveFactorY -= (std::abs(y) > 15) ? y / 100.0f * 3.0f : 0.0f;

		inputs.fireBullet = sf::Joystick::isButtonPressed(0, 0) && (recoil == 0);
	}
	else
	{
		inputs.moveFactorY += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ? 3.0f : 0.0f;
		inputs.moveFactorY += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ? -3.0f : 0.0f;
		inputs.moveFactorX += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ? 3.0f : 0.0f;
		inputs.moveFactorX += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ? -3.0f : 0.0f;
		inputs.fireBullet = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	}
	return retval;
}

void GameScene::fireBullet(const GameObject& object, const bool isEnemy)
{
	Bullet& b1 = getAvailableObject(isEnemy ? enemyBullets : playerBullets);
	Bullet& b2 = getAvailableObject(isEnemy ? enemyBullets : playerBullets);

	sf::Vector2f bulletOffset = sf::Vector2f(object.getGlobalBounds().width / 3, 0.f);
	b1.setPosition(object.getPosition() - bulletOffset);
	b2.setPosition(object.getPosition() + bulletOffset);
	b1.playSound();

	if (!isEnemy && player.getHasBonus()) {
		Bullet& b3 = getAvailableObject(playerBullets);
		b3.setPosition(object.getPosition());
	}

	inputs.fireBullet = false;
	recoil = MAX_RECOIL;
}

void GameScene::spawnBonus(const sf::Vector2f& enemyPosition)
{
	nbOfEnemyDeaths++;

	Random randomGenerator;
	srand(static_cast<unsigned int>(time(nullptr)));
	double randomValue = randomGenerator.nextDouble();
	srand(static_cast<unsigned int>(time(nullptr)));
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

unsigned int GameScene::getScore() const
{
	return score;
}

void GameScene::notify(Event event, const void* data)
{
	switch (event)
	{
	case Event::NONE:
		break;
	case Event::HEALTH_PICKED_UP:
	{
		score += SCORE_GAIN_PTS;
		Publisher::notifySubscribers(Event::SCORE_UPDATED, this);
		break;
	}
	case Event::GUN_PICKED_UP:
	{
		score += SCORE_GAIN_PTS;
		Publisher::notifySubscribers(Event::SCORE_UPDATED, this);
		break;
	}
	case Event::ENEMY_KILLED:
	{
		const Enemy* enemy = static_cast<const Enemy*>(data);
		score += SCORE_GAIN_PTS;
		spawnBonus(enemy->getPosition());
		Publisher::notifySubscribers(Event::SCORE_UPDATED, this);
		break;
	}
	default:
		break;
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