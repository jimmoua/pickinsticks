#include "window.h"

namespace {
  static sf::RenderWindow myRenderWindow;
  constexpr unsigned short int winResX = 640u;
  constexpr unsigned short int winResY = 480u;
}

void game::window::init() {
  // Create a window with video modes of specific resolutions. The title is
  // called "Game" and do not allow for the window to be resizable.
  myRenderWindow.create(sf::VideoMode(winResX, winResY),
                        "Game",
                        sf::Style::Close);
  myRenderWindow.setFramerateLimit(60u);
}

sf::RenderWindow* game::window::getWindow() { return &myRenderWindow; }

const unsigned short int& game::window::gwinResX() {
  return winResX;
}


const unsigned short int& game::window::gwinResY() {
  return winResY;
}
