#include "stdafx.h"
#include "ScoreScene.h"
#include "game.h"

ScoreScene::ScoreScene()
    : Scene(SceneType::SCORE_SCENE)
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
}

bool ScoreScene::init()
{
    if (scoreContentManager.loadContent() == false)
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

bool ScoreScene::handleEvents(sf::RenderWindow& window)
{
    bool retval = false;
    sf::Event event;
    while (window.pollEvent(event))
    {
        //x sur la fenêtre
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
        {
            window.close();
            retval = true;
        }
        if (event.type == sf::Event::KeyPressed) {

            // Écrire nom
        }
    }
    return retval;

}
