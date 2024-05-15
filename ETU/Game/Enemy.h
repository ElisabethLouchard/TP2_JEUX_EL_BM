#pragma once
#include "AnimatedGameObject.h"
#include "EnemyExplosionAnimation.h"
#include "EnemyIdleAnimation.h"
class Enemy :
	public AnimatedGameObject
{
public:
	Enemy();
	Enemy(const Enemy& src);
	virtual bool init(const ContentManager& contentManager) override;
	bool update(float deltaT, const Inputs& inputs) override;
	void onHit();
	void onDying();
	void loadEnemySound(const sf::SoundBuffer& soundbuffer);
	bool isAlive();
private:
	void speak();
	bool isDead;
	bool isExploding = false;
	int nbOfHit = 0;
	sf::Sound enemyKilledSound;
	sf::Clock explosionTimer;
	sf::Clock respawnTimer;
};

