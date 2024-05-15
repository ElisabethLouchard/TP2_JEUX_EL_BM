#include "stdafx.h"
#include "GameScene.h"
#include "game.h"
#include "GameContentManager.h"
#include "random.h"

const float GameScene::TIME_BETWEEN_FIRE = 0.5f;
const float spawnInterval = 0.01f;
const float BONUS_SPAWN_CHANCE = 0.2f;

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

	for (Enemy& e : enemies)
	{
		for (Bullet& b : bullets)
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
	for (const LifeBonus& b : listLifeBonus)
		b.draw(window);
	for (const WeaponBonus& b : listWeaponBonus)
		b.draw(window);
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
		enemy.setPosition(sf::Vector2f(i * (float)Game::GAME_WIDTH / 10.0f, -50.0f * (float)(rand() % 100)));
		enemies.push_back(enemy);
		enemy.loadEnemySound(gameContentManager.getEnemyKilledSoundBuffer());
	}

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
