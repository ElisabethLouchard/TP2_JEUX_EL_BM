#pragma once
#include "Scene.h"
#include "Inputs.h"
#include "Player.h"
#include "GameContentManager.h"
#include "Hud.h"
class GameScene :
    public Scene
{
public:
    // Héritées via Scene
    GameScene();
    ~GameScene();
    virtual SceneType update() override;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual bool init() override;
    virtual bool uninit() override;
    virtual bool handleEvents(sf::RenderWindow& window) override;
private:
    Inputs inputs;
    Player player;
    Hud hud;
    GameContentManager gameContentManager;
    sf::Texture gameBackgroundTexture;
    sf::Sprite gameBackground;
    bool hasTransition = false;
};

