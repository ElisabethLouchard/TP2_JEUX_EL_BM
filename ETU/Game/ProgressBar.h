#include "GameObject.h"
class ProgressBar : public GameObject{

public:
    ProgressBar();

    void init(float width, float height, float maxValue);
    void setCurrentValue(float value);
    float getCurrentValue() const;
   // virtual void setPosition(float x, float y) override;
    //virtual void draw(sf::RenderWindow& window) const override;

private:
    sf::RectangleShape bar;
    float maxValue;
    float currentValue;
};