#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "window.h"
#include "map.h"
#include "character.h"
#include <SFML/Audio.hpp>

namespace game {
  void update();
  void init();
  void playLoot();
  const sf::Text& getText();
  void updateScore();
  void run();
}
