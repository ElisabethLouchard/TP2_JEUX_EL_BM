#include "stdafx.h"
#include "ScoreContentManager.h"

bool ScoreContentManager::loadContent()
{
	if (!scoreBackgroundTexture.loadFromFile("Assets\\Sprites\\Level01\\SpaceBackground.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Assets\\Fonts\\Level01\\emulogic.ttf"))
	{
		return false;
	}
	return true;
}

const sf::Texture& ScoreContentManager::getBackgroundTexture() const
{
	return scoreBackgroundTexture;
}

const sf::Font& ScoreContentManager::getFont() const
{
	return font;
}

ScoreContentManager::ScoreContentManager()
	: ContentManager()
{
}