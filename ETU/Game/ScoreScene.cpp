#include "stdafx.h"
#include "ScoreScene.h"
#include "game.h"

ScoreScene::ScoreScene()
	: Scene(SceneType::SCORE_SCENE)
	, inputFinished(false)
{

}

ScoreScene::~ScoreScene()
{

}
SceneType ScoreScene::update()
{
	SceneType retval = getSceneType();

	if (hasTransition)
	{
		pause();
		return SceneType::TITLE_SCENE;
	}

	return retval;
}

void ScoreScene::draw(sf::RenderWindow& window) const
{
	window.draw(scoreBackground);
	window.draw(title);
	window.draw(subtitle);
	window.draw(instructions);
	window.draw(inputText);
	window.draw(scoreText);

	for (const auto& playerName : playerNames)
	{
		window.draw(playerName);
	}

	for (const auto& playerScore : playerScores)
	{
		window.draw(playerScore);
	}
}

bool ScoreScene::init()
{
	if (!scoreContentManager.loadContent())
	{
		return false;
	}

	scoreBackground.setTexture(scoreContentManager.getBackgroundTexture());

	title.setFont(scoreContentManager.getFont());
	title.setString("GAME OVER");
	title.setCharacterSize(60);
	title.setFillColor(sf::Color::Red);
	title.setOrigin(title.getGlobalBounds().width / 2.0f, title.getGlobalBounds().height / 2.0f);
	title.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 9.0f);

	subtitle.setFont(scoreContentManager.getFont());
	subtitle.setString("LEADERBOARD");
	subtitle.setCharacterSize(40);
	subtitle.setOrigin(subtitle.getGlobalBounds().width / 2.0f, subtitle.getGlobalBounds().height / 2.0f);
	subtitle.setPosition(Game::GAME_WIDTH / 2.0f, title.getPosition().y + title.getGlobalBounds().height + subtitle.getGlobalBounds().height);

	const int numEntries = 4;
	const float startX = Game::GAME_WIDTH / 3.0f;
	const float startY = Game::GAME_HEIGHT / 3.0f;
	const float offsetY = 50.0f;

	// Créez les entrées pour les noms et les scores
	for (int i = 0; i < numEntries; ++i)
	{
		sf::Text playerName;
		playerName.setFont(scoreContentManager.getFont());
		playerName.setString("_");
		playerName.setCharacterSize(25);
		playerName.setFillColor(sf::Color::Green);
		playerName.setPosition(startX, startY + i * offsetY);
		playerNames.push_back(playerName);

		sf::Text playerScore;
		playerScore.setFont(scoreContentManager.getFont());
		playerScore.setCharacterSize(25);
		playerScore.setString("0");
		playerScore.setFillColor(sf::Color::White);
		playerScore.setPosition(Game::GAME_WIDTH - startX, startY + i * offsetY);
		playerScores.push_back(playerScore);
	}

	// Positionnez inputText au-dessus du premier playerName
	inputText.setFont(scoreContentManager.getFont());
	inputText.setCharacterSize(25);
	inputText.setFillColor(sf::Color::White);
	inputText.setString("_");
	inputText.setPosition(startX, startY - offsetY);

	// Positionnez scoreText au-dessus du premier playerScore
	scoreText.setFont(scoreContentManager.getFont());
	scoreText.setCharacterSize(25);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setString("230");
	scoreText.setPosition(Game::GAME_WIDTH - startX, startY - offsetY);

	instructions.setFont(scoreContentManager.getFont());
	instructions.setString("PRESS ESC TO QUIT");
	instructions.setCharacterSize(25);
	instructions.setOrigin(instructions.getGlobalBounds().width / 2.0f, instructions.getGlobalBounds().height / 2.0f);
	instructions.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT - (Game::GAME_HEIGHT / 9.0f));

	return true;
}

bool ScoreScene::uninit()
{
	return true;
}

bool ScoreScene::isValidInput(const std::string& input)
{
	if (input.length() != 3)
	{
		return false;
	}

	for (char c : input)
	{
		if (!std::isalpha(c))
		{
			return false;
		}
	}

	return true;
}

// Source : Aidé de ChatGPT pour cette partie.
bool ScoreScene::handleEvents(sf::RenderWindow& window)
{
	bool retval = false;
	sf::Event event;
	while (window.pollEvent(event))
	{
		// x sur la fenêtre
		if (event.type == sf::Event::Closed)
		{
			window.close();
			retval = true;
		}

		if (!inputFinished)
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == '\b')
				{
					// Gérer la suppression
					if (!playerInput.empty())
					{
						playerInput.pop_back();
					}
				}
				else if (event.text.unicode == '\r')
				{
					// Gérer l'appui sur Enter (terminer la saisie ou valider)
					if (isValidInput(playerInput))
					{
						inputFinished = true;
						inputText.setString(playerInput); // Supprime le curseur
					}
				}
				else
				{
					// Ajouter le caractère si la longueur est inférieure à 3
					if (playerInput.length() < 3)
					{
						char enteredChar = static_cast<char>(event.text.unicode);
						if (std::isalpha(enteredChar)) // Vérifiez si c'est une lettre
						{
							enteredChar = std::toupper(enteredChar); // Convertir en majuscule
							playerInput += enteredChar;
						}
					}
				}

				// Mettre à jour l'affichage du texte saisi
				if (!inputFinished)
				{
					inputText.setString(playerInput + "_"); // Ajoute un curseur à la fin
				}
			}
		}
		else
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				hasTransition = true;
				retval = true;
			}
			else if (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 1) // Vérifiez si le bouton B est pressé
			{
				hasTransition = true;
				retval = true;
			}
		}
	}
	return retval;
}
