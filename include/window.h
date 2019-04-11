#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

namespace game {

  namespace window {
    void init();
    sf::RenderWindow* getWindow();
  }
}

#endif
