#include "stdafx.h"
#include "GameContentManager.h"

bool GameContentManager::loadContent()
{
	if (!gameBackgroundTexture.loadFromFile("Assets\\Sprites\\Level01\\SpaceBackground.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Assets\\Fonts\\Level01\\emulogic.ttf"))
	{
		return false;
	}

	if (!gameMusicSoundBuffer.loadFromFile("Assets\\Music\\Title\\SkyFire (Title Screen).ogg"))
	{
		return false;
	}

	if (!enemyTexture.loadFromFile("Assets\\Sprites\\Level01\\NES - The Guardian Legend - Bosses.bmp"))
	{
		return false;
	}

	if (!shipAnimationTexture.loadFromFile("Assets\\Sprites\\Level01\\NES - The Guardian Legend - The Guardian Alyssa.png"))
		return false;
	return true;
}

const sf::Texture& GameContentManager::getBackgroundTexture() const
{
	return gameBackgroundTexture;
}

const sf::Texture& GameContentManager::getShipAnimationTexture() const
{
	return shipAnimationTexture;
}

const sf::Font& GameContentManager::getFont() const
{
	return font;
}

const sf::SoundBuffer& GameContentManager::getGameMusicSoundBuffer() const
{
	return gameMusicSoundBuffer;
}

const sf::Texture& GameContentManager::getEnemyTexture() const
{
	return enemyTexture;
}

GameContentManager::GameContentManager()
	: ContentManager()
{
}
