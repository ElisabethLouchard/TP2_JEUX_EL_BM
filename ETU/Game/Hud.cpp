#include "stdafx.h"
#include "Hud.h"
#include "GameContentManager.h"
#include "game.h"

const std::string NB_POINTS = "Score : ";
const std::string NB_LIVES = "Vies : ";
const std::string NB_BONUS = "Bonus : ";

Hud::Hud()
{

}

void Hud::initialize(const GameContentManager& gameContentManager)
{
	hudView = sf::View(sf::FloatRect(0, 0, (float)Game::GAME_WIDTH, (float)Game::GAME_HEIGHT));

	const sf::Font& font = gameContentManager.getFont();
	scoreText.setFont(font);
	scoreText.setCharacterSize(18);
	scoreText.setOutlineColor(sf::Color::White);
	scoreText.setString(NB_POINTS + std::to_string(nbOfPoints));
	scoreText.setPosition(0, Game::GAME_HEIGHT - (scoreText.getLocalBounds().height*2));

	nbOfLivesText.setFont(font);
	nbOfLivesText.setCharacterSize(18);
	nbOfLivesText.setOutlineColor(sf::Color::White);
	nbOfLivesText.setPosition(Game::GAME_WIDTH - (scoreText.getLocalBounds().width*2), Game::GAME_HEIGHT - (scoreText.getLocalBounds().height*2));
	nbOfLivesText.setString(NB_LIVES + std::to_string(nbOfLives));

	bonusText.setFont(font);
	bonusText.setCharacterSize(18);
	bonusText.setOutlineColor(sf::Color::White);
	bonusText.setPosition(Game::GAME_WIDTH - scoreText.getLocalBounds().width, Game::GAME_HEIGHT - (scoreText.getLocalBounds().height * 2));
	bonusText.setString(NB_BONUS + std::to_string(bonus));
}

void Hud::updateNbOfLiveText(int nbOfLives)
{
	nbOfLivesText.setString(NB_LIVES + std::to_string(nbOfLives));
}

void Hud::updateScoreText(int score)
{
	scoreText.setString(NB_POINTS + std::to_string(score));
}

void Hud::updateBonusText(int bonus)
{
	bonusText.setString(NB_BONUS + std::to_string(bonus));
}

void Hud::draw(sf::RenderWindow& window)  const
{
	window.setView(hudView);
	window.draw(scoreText);
	window.draw(nbOfLivesText);
	window.draw(bonusText);
}

