#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "Enemy.h"
#include "ProgressBar.h"
class EnemyBoss : public Enemy
{
public:
    EnemyBoss();
    EnemyBoss(const EnemyBoss& src);
    bool init(const ContentManager& contentManager) override;
    bool update(float deltaT, const Inputs& inputs) override;
    void onHit() override;
    void kill() override;
    void draw(sf::RenderWindow& window) const override;
    void activate() override;
    void setDestination(const sf::Vector2f& dest);
private:
    float moveAngle;
    ProgressBar healthBar;
    int currentHealth = 10;
};

