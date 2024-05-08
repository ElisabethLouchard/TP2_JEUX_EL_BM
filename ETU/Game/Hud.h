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
private:
	sf::View hudView;
	sf::Text scoreText;
	sf::Text nbOfLivesText;
	int nbOfLives = 5;
	int nbOfPoints = 0;
};
