#pragma once
#include "AnimatedGameObject.h"
//#include "LargeEnemyIdleAnimation.h"
//#include "LargeEnemyExplosionAnimation.h"
class Enemy :
	public AnimatedGameObject
{
public:
	Enemy();
	Enemy(const Enemy& src);
	virtual bool init(const ContentManager& contentManager) override;
	bool update(float deltaT, const Inputs& inputs) override;
	void onHit();
private:
	bool isDead;
	bool isExploding = false;
	sf::Clock explosionTimer;
	sf::Clock respawnTimer;
	float respawnDelay = 3.0f;
};
