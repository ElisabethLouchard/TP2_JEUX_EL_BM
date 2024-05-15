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
	const sf::SoundBuffer& getEnemyKilledSoundBuffer() const;
	const sf::Texture& getEnemyTexture() const;
	const sf::Texture& getBonusTexture() const;
	const sf::SoundBuffer& getLifeBonusSoundBuffer() const;
	const sf::SoundBuffer& getWeaponBonusSoundBuffer() const;

private:
	sf::Texture gameBackgroundTexture;
	sf::Texture shipAnimationTexture;
	sf::Texture enemyTexture;
	sf::Texture bonusTexture;
	sf::Sprite gameBackground;
	sf::Font font;
	sf::SoundBuffer gameMusicSoundBuffer;
	sf::SoundBuffer enemyKilledSoundBuffer;
	sf::SoundBuffer lifeBonusSoundBuffer;
	sf::SoundBuffer weaponBonusSoundBuffer;
};

