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

private:
	sf::Texture gameBackgroundTexture;
	sf::Texture shipAnimationTexture;
	sf::Sprite gameBackground;
	sf::Font font;
	sf::SoundBuffer gameMusicSoundBuffer;
};

