#pragma once
#include "Scene.h"
#include "ContentManager.h"
#include "ScoreContentManager.h"
class ScoreScene :
    public Scene
{
public:
    // Héritées via Scene
    ScoreScene();
    ~ScoreScene();
    virtual SceneType update() override;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual bool init() override;
    virtual bool uninit() override;
    bool isValidInput(const std::string& input);
    virtual bool handleEvents(sf::RenderWindow& window) override;
private:
    bool inputFinished;
    ScoreContentManager scoreContentManager;
    sf::Texture scoreBackgroundTexture;
    sf::Sprite scoreBackground;
    sf::Text title;
    sf::Text subtitle;
    sf::Text instructions;
    std::string playerInput;
    sf::Text inputText;
    sf::Text scoreText;
    std::vector<sf::Text> playerNames;
    std::vector<sf::Text> playerScores;
    bool hasTransition = false;
};

