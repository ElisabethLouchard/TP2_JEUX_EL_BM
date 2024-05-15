#pragma once
#include "Bonus.h"
class LifeBonus : public Bonus
{
public:
	LifeBonus();
	bool update(float elapsedTime) override;
	void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb) override;
};

