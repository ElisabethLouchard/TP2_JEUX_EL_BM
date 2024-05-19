#pragma once
#include "AnimatedGameObject.h"

struct Inputs;
class Player :
    public AnimatedGameObject
{
public:
    static const float SPEED;
    static const unsigned int NB_INITIAL_LIVES;
    static const float PLAYER_INVINCIBILITY_DURATION;
    static const sf::Color RESET_COLOR;

    Player();
    virtual bool init(const ContentManager& contentManager) override;
    bool update(float deltaT, const Inputs& inputs);
    void adjustCrossingViewLimits();
    void kill();
    void reduceLifePts();
    bool isAlive() const;
    bool getHasBonus() const;
    void pickUpHealthBonus();
    void pickUpGunBonus();
    void reduceBonusPts();
    void activateBonus();
    unsigned int getNbOfLives() const;
    unsigned int getNbOfBonusPts() const;
private:
    void updateTimeBeforeRevive(float elapsedTime);
    void revive();
    float invincibilityTimer;
    unsigned int nbOfLives;
    unsigned int nbOfBonusPts;
    bool isInvincible;
};