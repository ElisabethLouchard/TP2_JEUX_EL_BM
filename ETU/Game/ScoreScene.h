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
    virtual bool handleEvents(sf::RenderWindow& window) override;
private:
    ScoreContentManager scoreContentManager;
    sf::Texture scoreBackgroundTexture;
    sf::Sprite scoreBackground;
    sf::Text title;
    sf::Text subtitle;
    sf::Text instructions;
    bool hasTransition = false;
};

