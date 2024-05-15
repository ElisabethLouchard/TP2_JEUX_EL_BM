#pragma once
#include "Scene.h"
#include "TitleContentManager.h"
class TitleScene :
    public Scene
{
public:
  // Héritées via Scene
  TitleScene();
  ~TitleScene();
  virtual SceneType update() override;
  virtual void draw(sf::RenderWindow& window) const override;
  virtual bool init() override;
  virtual bool uninit() override;
  virtual bool handleEvents(sf::RenderWindow& window) override;
private:
  TitleContentManager titleContentManager;
  sf::Sprite menuImage;
  sf::Text instructions;
  sf::Music gameMusic;
  bool hasTransition = false;
};

