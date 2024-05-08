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
  window.draw(instructions);
}

bool TitleScene::init()
{
    if (titleContentManager.loadContent() == false)
    {
        return false;
    }
    menuImage.setTexture(titleContentManager.getTitleTexture());
    menuImage.setOrigin(menuImage.getTexture()->getSize().x / 2.0f, menuImage.getTexture()->getSize().y / 2.0f);
    menuImage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 2.0f);
    instructions.setFont(titleContentManager.getFont());
    instructions.setString("Press any key to start");
    instructions.setCharacterSize(30);
    instructions.setPosition(Game::GAME_WIDTH / 2.0f - instructions.getGlobalBounds().width / 2.0f,
        Game::GAME_HEIGHT / 2 + (menuImage.getGlobalBounds().height / 2.0f) + 20);
    gameMusic.setBuffer(titleContentManager.getGameMusicSoundBuffer());
    gameMusic.play();
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
