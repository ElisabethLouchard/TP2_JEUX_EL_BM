#include "stdafx.h"
#include "EnemyExplosionAnimation.h"
#include "GameContentManager.h"

static const float ANIMATION_LENGTH;

EnemyExplosionAnimation::EnemyExplosionAnimation(sf::Sprite& s) : LinearAnimation(s, ANIMATION_LENGTH, false)
{
}

bool EnemyExplosionAnimation::init(const ContentManager& contentManager)
{
	const GameContentManager& gameContentManager = (const GameContentManager&)contentManager;
	const sf::Texture& texture = gameContentManager.getEnemyTexture();
	frames.push_back(AnimationFrame(texture, sf::IntRect(28, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(101, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(174, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(247, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(320, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(393, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(466, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(539, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(612, 917, 65, 96)));
	return true;
}