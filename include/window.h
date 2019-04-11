#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

namespace game {

  namespace window {
    void init();
    sf::RenderWindow* getWindow();
    const sf::Vector2u getWinReso();
  }
}

#endif
