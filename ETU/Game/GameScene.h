#pragma once
#include "Scene.h"
#include "Inputs.h"
#include "Player.h"
#include "Enemy.h"
#include "GameContentManager.h"
#include "Hud.h"
#include "Bullet.h"
#include <list>

class GameScene :
    public Scene
{
public:
    static const float TIME_BETWEEN_FIRE;

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
    void fireBullet(const sf::Vector2f& position);
    GameContentManager gameContentManager;
    std::list<Enemy> enemies;
    sf::Texture gameBackgroundTexture;
    sf::Sprite gameBackground;
    bool hasTransition = false;
    std::list<Bullet> bullets;
    float timeSinceLastFire;
    float timeSinceLastSpawn;
};

