#pragma once
#include "Scene.h"
#include "ContentManager.h"
class ScoreScene :
    public Scene
{
public:
    // H�rit�es via Scene
    ScoreScene();
    ~ScoreScene();
    virtual SceneType update() override;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual bool init() override;
    virtual bool uninit() override;
    virtual bool handleEvents(sf::RenderWindow& window) override;
private:
    sf::Texture menuImageTexture;
    sf::Sprite menuImage;
    bool hasTransition = false;
};

