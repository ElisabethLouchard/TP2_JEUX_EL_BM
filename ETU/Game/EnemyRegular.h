#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Audio/Sound.hpp>
#include "Enemy.h"
class EnemyRegular : public Enemy
{
public:
    EnemyRegular();
    EnemyRegular(const EnemyRegular& src);
    bool init(const ContentManager& contentManager) override;
    bool update(float deltaT, const Inputs& inputs) override;
private:
    sf::Sound enemyKilledSound;
};

