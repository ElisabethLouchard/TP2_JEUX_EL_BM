#include "stdafx.h"
#include "ScoreScene.h"
#include "GameScene.h"
#include "ScoreManager.cpp"
#include "game.h"
#include "PlayerStats.h"

#define MAX_STATS 5

ScoreScene::ScoreScene()
    : Scene(SceneType::SCORE_SCENE), inputFinished(false), playerInput(""), currentPlayerScore(0)
{
    // Initialisez les scores des joueurs
    for (int i = 0; i < MAX_STATS; ++i)
    {
        PlayerStats ps;
        memset(ps.name, 0, NAME_LENGTH);
        ps.score = 0;
        playerStats.push_back(ps);
    }
}

ScoreScene::~ScoreScene()
{
}

SceneType ScoreScene::update()
{
    SceneType retval = getSceneType();

    if (hasTransition)
    {
        hasTransition = false;
        return SceneType::NONE;
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

    if (!readFromFile("scores.bin", playerStats.data()))
    {
        // Si la lecture échoue, initialisez avec des valeurs par défaut
        for (auto& ps : playerStats)
        {
            strncpy_s(ps.name, "---", NAME_LENGTH);
            ps.score = 0;
        }
    }

    currentPlayerScore = GameScene::scoreFinal.gameSceneResult.score;

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

    const float startX = Game::GAME_WIDTH / 3.0f;
    const float startY = Game::GAME_HEIGHT / 3.0f;
    const float offsetY = 50.0f;

    // Créez les entrées pour les noms et les scores
    for (int i = 0; i < MAX_STATS; ++i)
    {
        sf::Text playerName;
        playerName.setFont(scoreContentManager.getFont());
        playerName.setString(playerStats[i].name);
        playerName.setCharacterSize(25);
        playerName.setFillColor(sf::Color::White);
        playerName.setPosition(startX, startY + i * offsetY);
        playerNames.push_back(playerName);

        sf::Text playerScore;
        playerScore.setFont(scoreContentManager.getFont());
        playerScore.setCharacterSize(25);
        playerScore.setString(std::to_string(playerStats[i].score));
        playerScore.setFillColor(sf::Color::White);
        playerScore.setPosition(Game::GAME_WIDTH - startX, startY + i * offsetY);
        playerScores.push_back(playerScore);
    }

    // Positionnez inputText au-dessus du premier playerName
    inputText.setFont(scoreContentManager.getFont());
    inputText.setCharacterSize(25);
    inputText.setFillColor(sf::Color::Green);
    inputText.setString("_");
    inputText.setPosition(startX, startY - offsetY);

    // Positionnez scoreText au-dessus du premier playerScore
    scoreText.setFont(scoreContentManager.getFont());
    scoreText.setCharacterSize(25);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString(std::to_string(currentPlayerScore));
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

// Source : Aidé par ChatGPT.
void ScoreScene::addScore(const PlayerStats& newScore)
{
    playerStats.push_back(newScore);
    std::sort(playerStats.begin(), playerStats.end(), [](const PlayerStats& a, const PlayerStats& b) {
        return a.score > b.score;
        });
    if (playerStats.size() > MAX_STATS)
    {
        playerStats.pop_back();
    }

    // Mise à jour des affichages
    for (int i = 0; i < playerStats.size(); ++i)
    {
        playerNames[i].setString(playerStats[i].name);
        playerScores[i].setString(std::to_string(playerStats[i].score));
    }
}

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

                        // Ajouter le score du joueur
                        PlayerStats newStats;
                        strncpy_s(newStats.name, playerInput.c_str(), NAME_LENGTH);
                        newStats.score = currentPlayerScore;
                        addScore(newStats);

                        // Écrire les scores à jour dans le fichier
                        writeToFile("scores.bin", playerStats.data());
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
            // J'ai mis KeyReleased, car sinon, une fois sur TITLE_SCENE, la page se ferme (trop rapide).
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
			{
				hasTransition = true;
			}
			else if (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 1) // Vérifiez si le bouton B est pressé
			{
				hasTransition = true;
			}
		}
	}
	return retval;
}
