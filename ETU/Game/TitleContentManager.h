#pragma once
#include "ContentManager.h"
class TitleContentManager : public ContentManager
{
public:
	TitleContentManager();
	virtual bool loadContent() override;
	const sf::Texture& getTitleTexture() const;
	const sf::Font& getFont() const;
	const sf::SoundBuffer& getGameMusicSoundBuffer() const;

private:
	sf::Texture menuImageTexture;
	sf::Sprite menuImage;
	sf::Font font;
	sf::SoundBuffer gameMusicSoundBuffer;
};

