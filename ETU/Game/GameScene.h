#pragma once
#include "Scene.h"
#include "Inputs.h"
#include "Player.h"
#include "EnemyRegular.h"
#include "EnemyBoss.h"
#include "Enemy.h"
#include "GameContentManager.h"
#include "Hud.h"
#include "Bullet.h"
#include "LifeBonus.h"
#include "WeaponBonus.h"
#include "Bonus.h"
#include "EnemyBossIdleAnimation.h"
#include <list>

class GameScene : public Scene, Subscriber
{
public:
    static const unsigned int MAX_RECOIL;
    static const float TIME_BETWEEN_FIRE;
    static const float BONUS_SPAWN_CHANCE;
    static const float TIME_PER_FRAME;
    static const unsigned int NB_BULLETS;
    static const unsigned int NB_ENEMIES;
    static const unsigned int NB_BONUSES;
    static const unsigned int SCORE_GAIN_PTS;
    static const unsigned int REGULAR_ENEMY_DAMAGE;
    static const unsigned int BOSS_ENEMY_DAMAGE;

    static SceneResult scoreFinal;

    // Héritées via Scene
    GameScene();
    ~GameScene();
    virtual SceneType update() override;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual bool init() override;
    virtual bool uninit() override;
    virtual bool handleEvents(sf::RenderWindow& window) override;
    unsigned int getScore() const;
    void notify(Event event, const void* data) override;

private:
    // Entrées utilisateur
    Inputs inputs;

    // Entités du jeu
    Player player;
    EnemyBoss boss;
    std::list<EnemyRegular> enemies;
    std::list<LifeBonus> listLifeBonus;
    std::list<WeaponBonus> listWeaponBonus;
    std::list<Bullet> playerBullets;
    std::list<Bullet> enemyBullets;

    // Interface utilisateur
    Hud hud;

    // Ressources graphiques
    GameContentManager gameContentManager;
    sf::Texture gameBackgroundTexture;
    sf::Sprite gameBackground;

    // Variables de jeu
    unsigned int score;
    int recoil;
    float timeSinceLastFire;
    float timeSinceLastSpawn;
    int nbOfEnemyDeaths;
    bool hasScoreSceneBeenDisplayed;

    // Fonctions utilitaires
    void spawnBonus(const sf::Vector2f& enemyPosition);
    template<typename GameObject>
    GameObject& getAvailableObject(std::list<GameObject>& objects);
    void fireBullet(const GameObject& object, const bool isEnemy);
    void initializeBulletPool(std::list<Bullet>& bulletPool, const sf::Texture& texture, const bool isEnemy);
};
