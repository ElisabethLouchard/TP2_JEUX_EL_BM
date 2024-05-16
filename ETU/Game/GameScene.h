#pragma once
#include "Scene.h"
#include "Inputs.h"
#include "Player.h"
#include "Enemy.h"
#include "GameContentManager.h"
#include "Hud.h"
#include "Bullet.h"
#include "LifeBonus.h"
#include "WeaponBonus.h"
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
    void spawnBonus(const sf::Vector2f& enemyPosition);
    template<typename GameObject>
    GameObject& getAvailableObject(std::list<GameObject>& objects);
    GameContentManager gameContentManager;
    std::list<Enemy> enemies;
    std::list<LifeBonus> listLifeBonus;
    std::list<WeaponBonus> listWeaponBonus;
    std::list<Bullet> bullets;
    sf::Texture gameBackgroundTexture;
    sf::Sprite gameBackground;
    int nbOfLives = 5;
    int score = 100;
    int bonus = 0;
    bool hasTransition = false;
    float timeSinceLastFire;
    float timeSinceLastSpawn;
};

