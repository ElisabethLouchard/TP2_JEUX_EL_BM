#include "stdafx.h"
#include "TitleScene.h"

#include "game.h"

TitleScene::TitleScene()
  : Scene(SceneType::TITLE_SCENE)
{

}

TitleScene::~TitleScene()
{

}
SceneType TitleScene::update()
{
    SceneType retval = getSceneType();

    if (hasTransition)
    {
        pause();
        return SceneType::GAME_SCENE;
    }

    return retval;
}

void TitleScene::draw(sf::RenderWindow& window) const
{
  window.draw(menuImage);
}

bool TitleScene::init()
{
  if (!menuImageTexture.loadFromFile("Assets\\Sprites\\Title\\Title.png"))
    return false;
  menuImage.setTexture(menuImageTexture);
  menuImage.setOrigin(menuImage.getTexture()->getSize().x / 2.0f, menuImage.getTexture()->getSize().y / 2.0f);
  menuImage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 2.0f);

  return true;
}

bool TitleScene::uninit()
{
  return true;
}

bool TitleScene::handleEvents(sf::RenderWindow& window)
{
  bool retval = false;
  sf::Event event;
  while (window.pollEvent(event))
  {
    //x sur la fenêtre
    if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
    {
      window.close();
      retval = true;
    }
    if (event.type == sf::Event::KeyPressed) {
        
        hasTransition = true;
    }
  }
  return retval;

}
