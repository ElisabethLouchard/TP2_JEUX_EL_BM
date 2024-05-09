#include "stdafx.h"
#include "StandardEnemyIdleAnimation.h"
#include "ContentManager.h"

const float StandardEnemyIdleAnimation::ANIMATION_LENGTH = 0.0f;

StandardEnemyIdleAnimation::StandardEnemyIdleAnimation(sf::Sprite& s) : LinearAnimation(s, ANIMATION_LENGTH, false)
{

}

bool StandardEnemyIdleAnimation::init(const ContentManager& contentManager)
{
    //const sf::Texture& texture = contentManager.getLargeEnnemiesTexture();
    //frames.push_back(AnimationFrame(texture, sf::IntRect(10, 43, 50, 50)));
    return true;
}
