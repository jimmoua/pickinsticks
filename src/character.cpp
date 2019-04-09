#include "character.h"
#include <chrono>
#include <random>
playerClass::playerClass(const std::string &pathToCharacter) {
  this->playerTexture.loadFromFile(pathToCharacter);
  this->playerSprite.setTexture(this->playerTexture);

  // init sprite, which is a sprite facing down
  this->playerSprite.setTextureRect(sf::IntRect(0, 128, 64, 64)); 

  this->playerSprite.setOrigin(playerSprite.getTextureRect().width/2,
                               playerSprite.getTextureRect().height/2);
}

playerClass::playerClass() { }


entityClass::entityClass(const std::string &pathToEntity) {
  yeah.playerTexture.loadFromFile(pathToEntity);
  yeah.playerSprite.setTexture(yeah.playerTexture);
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generate(seed);
  std::uniform_int_distribution<int> width(64,640-64);
  std::uniform_int_distribution<int> height(64, 480-64);
  yeah.playerSprite.setPosition(width(generate), height(generate));
}

void entityClass::newPos(map &mapClassObject) {
  auto mo = &mapClassObject;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::uniform_int_distribution<int>
    width(64, mo->mapSprite.getTextureRect().width-64);
  std::uniform_int_distribution<int>
    height(64, mo->mapSprite.getTextureRect().height-64);
  this->yeah.playerSprite.setPosition(width(generator), height(generator));
}
