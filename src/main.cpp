#include "game.h"
#include "window.h"
#include "character.h"
#include "map.h"

int main() {
  map mo("./data/background.png");
  entityClass eo("./data/stick.png");
  playerClass po("./data/character.png");
  game::init();

  // I did not set the starting position of the character inside the class, so
  // I will do it inside main.
  po.playerSprite.setPosition(mo.mapSprite.getTextureRect().width/2,
                              mo.mapSprite.getTextureRect().height/2);
  while(game::window::getWindow()->isOpen())
  {
    sf::Event e;
    while(game::window::getWindow()->pollEvent(e))
    {
      if(e.type == sf::Event::Closed) {
        game::window::getWindow()->close();
      }
    }
    game::window::getWindow()->draw(mo.mapSprite);
    game::window::getWindow()->draw(po.playerSprite);
    game::window::getWindow()->draw(eo.yeah.playerSprite);
    game::window::getWindow()->draw(game::getText());

    // handling movement and stuff
    game::update(po, mo, eo);
    game::window::getWindow()->display();
  }
  return 0;
}
