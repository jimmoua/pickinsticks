#include "game.h"
#include "window.h"
#include "character.h"
#include "map.h"

int main() {
  map mo("./data/background.png");
  entityClass eo("./data/stick.png");
  playerClass po("./data/character.png");
  game engine;
  myWindowClass wo("Pickin' Sticks");

  // I did not set the starting position of the character inside the class, so
  // I will do it inside main.
  po.playerSprite.setPosition(mo.mapSprite.getTextureRect().width/2,
                              mo.mapSprite.getTextureRect().height/2);
  while(wo.myRenderWindow.isOpen())
  {
    sf::Event e;
    while(wo.myRenderWindow.pollEvent(e))
    {
      if(e.type == sf::Event::Closed) {
        wo.myRenderWindow.close();
      }
    }
    wo.myRenderWindow.draw(mo.mapSprite);
    wo.myRenderWindow.draw(po.playerSprite);
    wo.myRenderWindow.draw(eo.yeah.playerSprite);
    wo.myRenderWindow.draw(engine.getText());

    // handling movement and stuff
    engine.update(po, wo, mo, eo);
    wo.myRenderWindow.display();
  }
  return 0;
}
