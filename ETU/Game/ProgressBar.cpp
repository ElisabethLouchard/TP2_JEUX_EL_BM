#include "stdafx.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar() : maxValue(100), currentValue(100) {
}

void ProgressBar::init(float width, float height, float maxValue) {
    deactivate();
    this->maxValue = maxValue;
    this->currentValue = maxValue;
    bar.setSize(sf::Vector2f(width, height));
    bar.setFillColor(sf::Color::Red);
    bar.setOrigin(width / 2.0f, height / 2.0f);
}

void ProgressBar::setCurrentValue(float value) {
    float newWidth = bar.getSize().x * value / maxValue;
    bar.setSize(sf::Vector2f(newWidth, bar.getSize().y));
}

float ProgressBar::getCurrentValue() const {
    return currentValue;
}

void ProgressBar::setPosition(float x, float y) {
    bar.setPosition(x, y);
}

void ProgressBar::draw(sf::RenderWindow& window) const 
{ 
    window.draw(bar);
}


     