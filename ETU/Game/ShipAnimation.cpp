#include "stdafx.h"
#include "ShipAnimation.h"
#include "ContentManager.h"
#include "GameContentManager.h"
#include "Inputs.h"

ShipAnimation::ShipAnimation(sf::Sprite& s)
	: InputBasedAnimation(s)
	, nbFrameInState(0)
{
}

bool ShipAnimation::init(const ContentManager& contentManager)
{
	const GameContentManager& gameContentManager = (const GameContentManager&)contentManager;
	const sf::Texture& texture = gameContentManager.getShipAnimationTexture();
	frames.push_back(AnimationFrame(texture, sf::IntRect(324, 46, 14, 30)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(300, 48, 18, 30)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(270, 46, 23, 30)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(245, 48, 18, 30)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(226, 46, 14, 30)));
	return true;
}

void ShipAnimation::adjustNextFrame(const Inputs& inputs)
{
	if (inputs.moveFactorX < 0) {
		if (nbFrameInState < 49) {
			nbFrameInState++;
		}
	}
	else if (inputs.moveFactorX > 0) {
		if (nbFrameInState > 0) {
			nbFrameInState--;
		}
	}
	else {
		if (nbFrameInState > 24) {
			nbFrameInState--;
		}
		else if (nbFrameInState < 24) {
			nbFrameInState++;
		}
	}

	if (nbFrameInState > 40) {
		nextFrame = 0;
	}
	else if (nbFrameInState >= 30) {
		nextFrame = 1;
	}
	else if (nbFrameInState >= 20) {
		nextFrame = 2;
	}
	else if (nbFrameInState >= 10) {
		nextFrame = 3;
	}
	else {
		nextFrame = 4;
	}
}