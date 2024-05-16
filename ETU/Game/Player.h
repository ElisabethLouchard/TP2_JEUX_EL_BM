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
    bool getHasBonus() const;
    void deactivateBonus();
    void activateBonus();

private:
    bool hasBonus = false;
};