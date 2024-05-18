#include "stdafx.h"
#include "EnemyBossIdleAnimation.h"
#include "ContentManager.h"
#include "GameContentManager.h"

const float EnemyBossIdleAnimation::ANIMATION_LENGTH = 2.0f;

EnemyBossIdleAnimation::EnemyBossIdleAnimation(sf::Sprite& s) : CyclicAnimation(s, ANIMATION_LENGTH, true)
{

}

bool EnemyBossIdleAnimation::init(const ContentManager& contentManager)
{
	const GameContentManager& gameContentManager = (const GameContentManager&)contentManager;
	const sf::Texture& texture = gameContentManager.getEnemyTexture();
	frames.push_back(AnimationFrame(texture, sf::IntRect(32, 1905, 84, 124)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(133, 1905, 82, 126)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(232, 1905, 76, 139)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(329, 1905, 74, 143)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(426, 1905, 74, 147)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(522, 1905, 72, 147)));
	return true;
}

