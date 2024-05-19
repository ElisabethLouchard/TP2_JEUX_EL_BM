#pragma once
#include "Scene.h"
#include "ContentManager.h"
#include "ScoreContentManager.h"
#include "SFML/Graphics.hpp"
#include "PlayerStats.h"

class ScoreScene : public Scene
{
public:
    ScoreScene();
    ~ScoreScene();
    virtual SceneType update() override;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual bool init() override;
    virtual bool uninit() override;
    virtual bool handleEvents(sf::RenderWindow& window) override;

private:
    bool isValidInput(const std::string& input);
    void addScore(const PlayerStats& newScore);

private:
    bool inputFinished;
    std::string playerInput;
    int currentPlayerScore;
    bool hasTransition = false;

    ScoreContentManager scoreContentManager;

    sf::Text title;
    sf::Text subtitle;
    sf::Text instructions;
    sf::Text inputText;
    sf::Text scoreText;
    sf::Texture scoreBackgroundTexture;
    sf::Sprite scoreBackground;

    std::vector<sf::Text> playerNames;
    std::vector<sf::Text> playerScores;
    std::vector<PlayerStats> playerStats;

};
