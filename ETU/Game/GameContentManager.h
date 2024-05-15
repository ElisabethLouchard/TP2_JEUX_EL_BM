#pragma once
#include "ContentManager.h"
class GameContentManager : public ContentManager
{
public:
	GameContentManager();
	virtual bool loadContent() override;
	const sf::Texture& getBackgroundTexture() const;
	const sf::Texture& getShipAnimationTexture() const;
	const sf::Font& getFont() const;
	const sf::SoundBuffer& getGameMusicSoundBuffer() const;
	const sf::SoundBuffer& getPlayerBulletSoundBuffer() const;
	const sf::SoundBuffer& getEnemyBulletSoundBuffer() const;

private:
	sf::Texture gameBackgroundTexture;
	sf::Texture shipAnimationTexture;
	sf::Sprite gameBackground;
	sf::SoundBuffer playerBulletSoundBuffer;
	sf::SoundBuffer enemyBulletSoundBuffer;
	sf::Font font;
	sf::SoundBuffer gameMusicSoundBuffer;
};

