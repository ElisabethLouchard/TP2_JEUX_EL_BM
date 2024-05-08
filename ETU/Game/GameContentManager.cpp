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

	return true;
}

const sf::Texture& GameContentManager::getBackgroundTexture() const
{
	return gameBackgroundTexture;
}

const sf::Font& GameContentManager::getFont() const
{
	return font;
}

const sf::SoundBuffer& GameContentManager::getGameMusicSoundBuffer() const
{
	return gameMusicSoundBuffer;
}

GameContentManager::GameContentManager()
	: ContentManager()
{
}
