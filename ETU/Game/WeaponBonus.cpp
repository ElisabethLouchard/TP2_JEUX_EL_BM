#include "stdafx.h"
#include "WeaponBonus.h"

WeaponBonus::WeaponBonus()
	: Bonus()
{
}

bool WeaponBonus::update(float elapsedTime)
{
	return false;
}

void WeaponBonus::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb)
{
	setTextureRect(sf::IntRect(334, 107, 8, 8));
	Bonus::initialize(texture, initialPosition, sb);
}

void WeaponBonus::activate()
{
	Bonus::activate();
}
