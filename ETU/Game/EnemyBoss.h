#pragma once
#include "Enemy.h"
class EnemyBoss : public Enemy
{
public:
    EnemyBoss();
    EnemyBoss(const EnemyBoss& src);
    bool init(const ContentManager& contentManager) override;
    bool update(float deltaT, const Inputs& inputs) override;
    void onHit() override;
    void onDying() override;
};

