#pragma once
#include "ContentManager.h"
class GameContentManager : public ContentManager
{
public:
	GameContentManager();
	virtual bool loadContent() override;
	const sf::Texture& getBackgroundTexture() const;
	const sf::Font& getFont() const;
	const sf::SoundBuffer& getGameMusicSoundBuffer() const;

private:
	sf::Texture gameBackgroundTexture;
	sf::Sprite gameBackground;
	sf::Font font;
	sf::SoundBuffer gameMusicSoundBuffer;
};

