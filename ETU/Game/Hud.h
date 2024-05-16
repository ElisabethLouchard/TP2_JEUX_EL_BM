#pragma once
class GameContentManager;
class Hud
{
public:
	Hud();
	void draw(sf::RenderWindow& window)  const;
	void initialize(const GameContentManager& gameContentManager);
	void updateNbOfLiveText(int nbOfLives);
	void updateScoreText(int score);
	void updateBonusText(int bonus);
private:
	sf::View hudView;
	sf::Text scoreText;
	sf::Text nbOfLivesText;
	sf::Text bonusText;
	int nbOfLives = 5;
	int nbOfPoints = 100;
	int bonus = 0;
};
