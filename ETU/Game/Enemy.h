#pragma once
#include "AnimatedGameObject.h"
class Enemy :
	public AnimatedGameObject
{
public:
	static const short MAX_NB_OF_HITS;

	Enemy();
	Enemy(const Enemy& src);
	virtual bool init(const ContentManager& contentManager) override;
	virtual bool update(float deltaT, const Inputs& inputs) override;
	virtual void onHit();
	virtual void onDying();
	void loadEnemySound(const sf::SoundBuffer& soundbuffer);
	bool isAlive() const;
	bool getShouldFireBullet() const;
private:
	void speak();
	bool isDead;
	int nbOfHit;
	sf::Sound enemyKilledSound;
	float initialDelay;

protected:
	bool shouldFireBullets;
};

