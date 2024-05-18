#pragma once
#include "Scene.h"
#include "Inputs.h"
#include "Player.h"
#include "EnemyRegular.h"
#include "EnemyBoss.h"
#include "GameContentManager.h"
#include "Hud.h"
#include "Bullet.h"
#include "LifeBonus.h"
#include "WeaponBonus.h"
#include "EnemyBossIdleAnimation.h"
#include <list>

class GameScene :
    public Scene
{
public:
    static const unsigned int MAX_RECOIL;
    static const float TIME_BETWEEN_FIRE;
    static const float BONUS_SPAWN_CHANCE;
    static const float TIME_PER_FRAME;
    static const unsigned int NB_BULLETS;
    static const unsigned int NB_ENEMIES;

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
    void spawnBonus(const sf::Vector2f& enemyPosition);
    template<typename GameObject>
    GameObject& getAvailableObject(std::list<GameObject>& objects);
    int recoil = 0;
    void fireBullet(const GameObject& object, const bool isEnemy);
    void initializeBulletPool(std::list<Bullet>& bulletPool, const sf::Texture& texture, const bool isEnemy);
    GameContentManager gameContentManager;
    EnemyBoss boss;
    std::list<EnemyRegular> enemies;
    std::list<LifeBonus> listLifeBonus;
    std::list<WeaponBonus> listWeaponBonus;
    sf::Texture gameBackgroundTexture;
    sf::Sprite gameBackground;
    int nbOfLives = 5;
    int score = 100;
    int bonus = 0;
    bool hasTransition = false;
    std::list<Bullet> playerBullets;
    std::list<Bullet> enemyBullets;
    float timeSinceLastFire;
    float timeSinceLastSpawn;
    int nbOfEnemyDeaths;
};

