#pragma once
#include "ContentManager.h"

class ScoreContentManager : public ContentManager
{
public:
	ScoreContentManager();
	virtual bool loadContent() override;
	const sf::Texture& getBackgroundTexture() const;
	const sf::Font& getFont() const;

private:
	sf::Texture scoreBackgroundTexture;
	sf::Sprite scoreBackground;
	sf::Font font;
};

