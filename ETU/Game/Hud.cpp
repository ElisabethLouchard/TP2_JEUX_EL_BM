#include "stdafx.h"
#include "Hud.h"
#include "GameContentManager.h"
#include "game.h"
#include "GameScene.h"
#include "Publisher.h"

const std::string NB_POINTS = "Score : ";
const std::string NB_LIVES = "Vies : ";
const std::string NB_BONUS = "Bonus : ";

Hud::Hud()
{

}

void Hud::initialize(const GameContentManager& gameContentManager)
{
	Publisher::addSubscriber(*this, Event::GUN_PICKED_UP);
	Publisher::addSubscriber(*this, Event::HEALTH_PICKED_UP);
	Publisher::addSubscriber(*this, Event::SCORE_UPDATED);

	hudView = sf::View(sf::FloatRect(0, 0, (float)Game::GAME_WIDTH, (float)Game::GAME_HEIGHT));

	const sf::Font& font = gameContentManager.getFont();
	scoreText.setFont(font);
	scoreText.setCharacterSize(16);
	scoreText.setOutlineColor(sf::Color::White);
	scoreText.setString(NB_POINTS + std::to_string(0));

	nbOfLivesText.setFont(font);
	nbOfLivesText.setCharacterSize(16);
	nbOfLivesText.setOutlineColor(sf::Color::White);
	nbOfLivesText.setString(NB_LIVES + std::to_string(0));

	bonusText.setFont(font);
	bonusText.setCharacterSize(16);
	bonusText.setOutlineColor(sf::Color::White);
	bonusText.setString(NB_BONUS + std::to_string(0));

	// Calculate total width of all texts
	float totalWidth = scoreText.getLocalBounds().width + nbOfLivesText.getLocalBounds().width + bonusText.getLocalBounds().width;

	// Calculate spacing
	float spacing = (Game::GAME_WIDTH - totalWidth) / 4.0f;

	// Set positions
	scoreText.setPosition(spacing, Game::GAME_HEIGHT - (scoreText.getLocalBounds().height * 2));
	nbOfLivesText.setPosition(2 * spacing + scoreText.getLocalBounds().width, Game::GAME_HEIGHT - (scoreText.getLocalBounds().height * 2));
	bonusText.setPosition(3 * spacing + scoreText.getLocalBounds().width + nbOfLivesText.getLocalBounds().width, Game::GAME_HEIGHT - (scoreText.getLocalBounds().height * 2));
}

void Hud::updateNbOfLiveText(unsigned int nbOfLives)
{
	nbOfLivesText.setString(NB_LIVES + std::to_string(nbOfLives));
}

void Hud::updateScoreText(unsigned int score)
{
	scoreText.setString(NB_POINTS + std::to_string(score));
}

void Hud::updateBonusText(unsigned int bonus)
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

void Hud::notify(Event event, const void* data)
{
	switch (event)
	{
	case Event::NONE:
		break;
	case Event::HEALTH_PICKED_UP:
	{
		const Player* player = static_cast<const Player*>(data);
		updateNbOfLiveText(player->getNbOfLives());
		updateBonusText(player->getNbOfBonusPts());
		break;
	}
	case Event::GUN_PICKED_UP:
	{
		const Player* player = static_cast<const Player*>(data);
		updateBonusText(player->getNbOfBonusPts());
		break;
	}
	case Event::SCORE_UPDATED:
	{
		const GameScene* gameScene = static_cast<const GameScene*>(data);
		updateScoreText(gameScene->getScore());
		break;
	}
	default:
		break;
	}
}

