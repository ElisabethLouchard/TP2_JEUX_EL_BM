#pragma once
#include "Enemy.h"
class EnemyRegular : public Enemy
{
public:
    EnemyRegular();
    EnemyRegular(const EnemyRegular& src);
    bool init(const ContentManager& contentManager) override;
    bool update(float deltaT, const Inputs& inputs) override;
    void onHit() override;
    void onDying() override;
};

