#include "stdafx.h"
#include "GameContentManager.h"

bool GameContentManager::loadContent()
{
	if (!gameBackgroundTexture.loadFromFile("Assets\\Sprites\\Level01\\SpaceBackground.png"))
	{
		return false;
	}
	else
	{
		gameBackgroundTexture.setRepeated(true);
	}

	if (!font.loadFromFile("Assets\\Fonts\\Level01\\emulogic.ttf"))
	{
		return false;
	}

	if (!enemyTexture.loadFromFile("Assets\\Sprites\\Level01\\NES - The Guardian Legend - Bosses.bmp"))
	{
		return false;
	}

	if (!gameMusicSoundBuffer.loadFromFile("Assets\\Music\\Title\\SkyFire (Title Screen).ogg"))
	{
		return false;
	}

	if (!enemyKilledSoundBuffer.loadFromFile("Assets\\SoundFX\\Level01\\enemyKilled.wav"))
	{
		return false;
	}

	if (!bonusTexture.loadFromFile("Assets\\Sprites\\Level01\\NES - The Guardian Legend - Miscellaneous.bmp"))
	{
		return false;
	}

	if (!weaponBonusSoundBuffer.loadFromFile("Assets\\SoundFX\\Level01\\gunBonus.wav"))
	{
		return false;
	}

	if (!lifeBonusSoundBuffer.loadFromFile("Assets\\SoundFX\\Level01\\healthBonus.wav"))
	{
		return false;
	}

	if (!shipAnimationTexture.loadFromFile("Assets\\Sprites\\Level01\\NES - The Guardian Legend - The Guardian Alyssa.bmp"))
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

const sf::SoundBuffer& GameContentManager::getEnemyKilledSoundBuffer() const
{
	return enemyKilledSoundBuffer;
}

const sf::Texture& GameContentManager::getEnemyTexture() const
{
	return enemyTexture;
}

const sf::Texture& GameContentManager::getBonusTexture() const
{
	return bonusTexture;
}

const sf::SoundBuffer& GameContentManager::getLifeBonusSoundBuffer() const
{
	return weaponBonusSoundBuffer;
}

const sf::SoundBuffer& GameContentManager::getWeaponBonusSoundBuffer() const
{
	return lifeBonusSoundBuffer;
}

GameContentManager::GameContentManager()
	: ContentManager()
{
}
