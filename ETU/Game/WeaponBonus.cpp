#include "stdafx.h"
#include "WeaponBonus.h"

WeaponBonus::WeaponBonus()
	: Bonus()
{
}

void WeaponBonus::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb)
{
	setTextureRect(sf::IntRect(334, 107, 8, 8));
	Bonus::initialize(texture, initialPosition, sb);
}
