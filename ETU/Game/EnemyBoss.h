#pragma once
#include <SFML/System/Vector2.hpp>
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
    void setDestination(const sf::Vector2f& dest);
    bool getShouldFireBullet() const;
private:
    float moveAngle;
    bool shouldFireBullets;
};

