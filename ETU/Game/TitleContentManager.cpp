#include "stdafx.h"
#include "TitleContentManager.h"

bool TitleContentManager::loadContent()
{
	if (!menuImageTexture.loadFromFile("Assets\\Sprites\\Title\\Title.png"))
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

const sf::Texture& TitleContentManager::getTitleTexture() const
{
	return menuImageTexture;
}

const sf::Font& TitleContentManager::getFont() const
{
	return font;
}

const sf::SoundBuffer& TitleContentManager::getGameMusicSoundBuffer() const
{
	return gameMusicSoundBuffer;
}

TitleContentManager::TitleContentManager()
	: ContentManager()
{
}
