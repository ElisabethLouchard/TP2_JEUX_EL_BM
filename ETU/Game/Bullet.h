#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
	static const float BULLET_SPEED;
	static const unsigned long long TIME_TO_LIVE;
public:
	Bullet(const sf::Vector2f& initialPosition = sf::Vector2f(0, 0), const sf::Vector2f& initialThrust = sf::Vector2f(0, 0));
	Bullet(const Bullet& src);
	virtual bool init(const ContentManager& manager);
	bool update(float elapsedTime);

private:
	Bullet& operator=(const Bullet& rhs);
};

