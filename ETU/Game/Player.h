#pragma once
#include "AnimatedGameObject.h"

struct Inputs;
class Player :
    public AnimatedGameObject
{
public:
    static const float SPEED;

    Player();
    virtual bool init(const ContentManager& contentManager) override;
    bool update(float deltaT, const Inputs& inputs);
    void adjustCrossingViewLimits();
    void kill();
    bool isAlive() const;
    bool getHasBonus() const;
    void pickUpHealthBonus();
    void pickUpGunBonus();
    void deactivateBonus();
    void activateBonus();
    unsigned int getNbOfLives() const;
    unsigned int getNbOfBonusPts() const;
private:
    unsigned int nbOfLives = 5;
    unsigned int nbOfBonusPts = 0;
};