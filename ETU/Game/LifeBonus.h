#pragma once
#include "Bonus.h"
class LifeBonus : public Bonus
{
public:
	LifeBonus();
	void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb) override;
};

