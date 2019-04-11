#include "window.h"

namespace {
  static sf::RenderWindow myRenderWindow;
  const static sf::Vector2u window_reso(640, 480);
}

void game::window::init() {
  // Create a window with video modes of specific resolutions. The title is
  // called "Game" and do not allow for the window to be resizable.
  myRenderWindow.create(sf::VideoMode(window_reso.x, window_reso.y),
                        "Game",
                        sf::Style::Close);
  myRenderWindow.setFramerateLimit(60u);
}

sf::RenderWindow* game::window::getWindow() {
  return &myRenderWindow;
}

const sf::Vector2u game::window::getWinReso() {
  return window_reso;
}
