#include "stdafx.h"
#include "LifeBonus.h"
#include "Publisher.h"

LifeBonus::LifeBonus()
	: Bonus()
{
}

void LifeBonus::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb)
{
	Bonus::initialize(texture, initialPosition, sb);
	Bonus::setTextureRect(sf::IntRect(313, 108, 9, 8));
}
