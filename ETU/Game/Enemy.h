#pragma once
#include "AnimatedGameObject.h"
#include "EnemyExplosionAnimation.h"
class Enemy :
	public AnimatedGameObject
{
public:
	Enemy();
	Enemy(const Enemy& src);
	virtual bool init(const ContentManager& contentManager) override;
	virtual bool update(float deltaT, const Inputs& inputs) override;
	virtual void onHit();
	virtual void onDying();
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

