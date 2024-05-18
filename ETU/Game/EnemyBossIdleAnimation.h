#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "CyclicAnimation.h"
class EnemyBossIdleAnimation : public CyclicAnimation
{
	static const float ANIMATION_LENGTH;
public:
	EnemyBossIdleAnimation(sf::Sprite& s);
	bool init(const ContentManager& contentManager) override;
};

