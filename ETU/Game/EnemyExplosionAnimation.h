#pragma once
#include "LinearAnimation.h"
class EnemyExplosionAnimation : public LinearAnimation
{
public:
	EnemyExplosionAnimation(sf::Sprite& s);
	bool init(const ContentManager& contentManager) override;

private:
	const float ANIMATION_LENGTH = 0.75;
};

