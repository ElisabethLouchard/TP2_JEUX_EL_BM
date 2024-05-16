#pragma once
#include "Bonus.h"
class WeaponBonus : public Bonus
{
public:
	WeaponBonus();
	void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb) override;
};

