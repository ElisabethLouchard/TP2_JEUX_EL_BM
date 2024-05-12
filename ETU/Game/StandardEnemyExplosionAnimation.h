#pragma once
#include "LinearAnimation.h"
class StandardEnemyIdleAnimation : public LinearAnimation
{
	static const float ANIMATION_LENGTH;
public:
	StandardEnemyIdleAnimation(sf::Sprite& s);
	bool init(const ContentManager& contentManager) override;
};

