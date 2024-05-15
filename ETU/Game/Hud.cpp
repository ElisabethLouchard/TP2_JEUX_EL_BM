#include "stdafx.h"
#include "Hud.h"
#include "GameContentManager.h"
#include "game.h"

const std::string NB_POINTS = "Nombre de points : ";
const std::string NB_LIVES = "Nombre de vies : ";

Hud::Hud()
{

}

void Hud::initialize(const GameContentManager& gameContentManager)
{
	hudView = sf::View(sf::FloatRect(0, 0, (float)Game::GAME_WIDTH, (float)Game::GAME_HEIGHT));

	const sf::Font& font = gameContentManager.getFont();
	scoreText.setFont(font);
	scoreText.setCharacterSize(15);
	scoreText.setOutlineColor(sf::Color::White);
	scoreText.setString(NB_POINTS + std::to_string(nbOfPoints));
	scoreText.setPosition(0, Game::GAME_HEIGHT - scoreText.getLocalBounds().height);

	nbOfLivesText.setFont(font);
	nbOfLivesText.setCharacterSize(15);
	nbOfLivesText.setOutlineColor(sf::Color::White);
	nbOfLivesText.setPosition(Game::GAME_WIDTH - scoreText.getLocalBounds().width, Game::GAME_HEIGHT - scoreText.getLocalBounds().height);
	nbOfLivesText.setString(NB_LIVES + std::to_string(nbOfLives));
}

void Hud::updateNbOfLiveText(int nbOfLives)
{
	nbOfLivesText.setString(NB_LIVES + std::to_string(nbOfLives));
}

void Hud::updateScoreText(int score)
{
	scoreText.setString(NB_POINTS + std::to_string(score));
}

void Hud::draw(sf::RenderWindow& window)  const
{
	window.setView(hudView);
	window.draw(scoreText);
	window.draw(nbOfLivesText);
}

