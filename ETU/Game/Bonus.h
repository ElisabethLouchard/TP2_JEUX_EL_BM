#pragma once
#include "GameObject.h"
class Bonus : public GameObject
{
public:
	Bonus(const sf::Vector2f& initialPosition = sf::Vector2f(0, 0));
	Bonus(const Bonus& src);
	Bonus& operator=(const Bonus& rhs);
	void draw(sf::RenderWindow& window) const;
	virtual bool update(float elapsedTime);
	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb);
	void playSound();
private:
	sf::Sound soundBonus;
	float timeSinceLaunch;
};