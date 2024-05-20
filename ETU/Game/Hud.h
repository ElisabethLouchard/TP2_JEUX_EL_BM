#pragma once
class GameContentManager;
#include "Subscriber.h"

class Hud : public Subscriber
{
public:
	Hud();
	~Hud();
	void draw(sf::RenderWindow& window)  const;
	void initialize(const GameContentManager& gameContentManager);
	void notify(Event event, const void* data) override;
private:
	void updateNbOfLiveText(unsigned int nbOfLives);
	void updateScoreText(unsigned int score);
	void updateBonusText(unsigned int bonus);
	sf::View hudView;
	sf::Text scoreText;
	sf::Text nbOfLivesText;
	sf::Text bonusText;
};
