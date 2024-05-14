#pragma once
#include "CyclicAnimation.h"
class EnemyIdleAnimation : public CyclicAnimation
{
	static const float ANIMATION_LENGTH;
public:
	EnemyIdleAnimation(sf::Sprite& s);
	bool init(const ContentManager& contentManager) override;
};

