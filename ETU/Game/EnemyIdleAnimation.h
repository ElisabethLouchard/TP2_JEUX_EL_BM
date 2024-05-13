#pragma once
#include "LinearAnimation.h"
class EnemyIdleAnimation : public LinearAnimation
{
	static const float ANIMATION_LENGTH;
public:
	EnemyIdleAnimation(sf::Sprite& s);
	bool init(const ContentManager& contentManager) override;
};

