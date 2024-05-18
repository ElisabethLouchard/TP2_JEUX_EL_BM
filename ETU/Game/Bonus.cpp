#include "stdafx.h"
#include "Bonus.h"
#include "ContentManager.h"
#include "game.h"

Bonus::Bonus(const sf::Vector2f& initialPosition)
	: GameObject()
	, timeSinceLaunch(0)
{
	setPosition(initialPosition);
}

Bonus::Bonus(const Bonus& src)
	:GameObject(src), soundBonus(src.soundBonus), timeSinceLaunch(src.timeSinceLaunch)
{
	GameObject::initialize(*src.getTexture(), src.getPosition());
}

Bonus& Bonus::operator=(const Bonus& rhs)
{
	if (this != &rhs)
	{
		GameObject::operator=(rhs);
		GameObject::initialize(*rhs.getTexture(), rhs.getPosition());
		soundBonus = rhs.soundBonus;
	}
	return *this;
}

bool Bonus::update(float elapsedTime)
{
	move(sf::Vector2f(0, 5));
	timeSinceLaunch += elapsedTime;

	if (timeSinceLaunch >= 0.2f)
	{
		timeSinceLaunch = 0.0f;

		if (getScale() == sf::Vector2f(4, 4)) {
			setScale(5, 5);
		}
		else {
			setScale(4, 4);
		}
	}
	return true;
}


void Bonus::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb)
{
	GameObject::initialize(texture, initialPosition);
	soundBonus.setBuffer(sb);
	setScale(4, 4);
	timeSinceLaunch = 0.0f;
}

void Bonus::deactivate()
{
	GameObject::deactivate();
	soundBonus.play();
}