#pragma once
#include "Scene.h"
#include "Inputs.h"
#include "Player.h"
#include "GameContentManager.h"
#include "Hud.h"
#include "Bullet.h"
#include <list>

class GameScene :
    public Scene
{
public:
    static const unsigned int MAX_RECOIL;
    static const float TIME_BETWEEN_FIRE;
    static const float TIME_PER_FRAME;
    static const unsigned int NB_BULLETS;

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
    int recoil = 0;
    template<typename GameObject>
    GameObject& getAvailableObject(std::list<GameObject>& objects);
    void fireBullet(const GameObject& object, const bool isEnemy);
    void initializeBulletPool(std::list<Bullet>& bulletPool, const sf::Texture& texture, const bool isEnemy);
    GameContentManager gameContentManager;
    sf::Texture gameBackgroundTexture;
    sf::Sprite gameBackground;
    bool hasTransition = false;
    std::list<Bullet> playerBullets;
    std::list<Bullet> enemyBullets;
    float timeSinceLastFire;
};

