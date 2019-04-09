#include "window.h"

myWindowClass::myWindowClass(const std::string &titleName) {
  auto vm = sf::VideoMode(window_reso.x, window_reso.y);
  myRenderWindow.create(vm, titleName, sf::Style::Close);
  myRenderWindow.setFramerateLimit(60);
}

myWindowClass::myWindowClass() {
  auto vm = sf::VideoMode(window_reso.x, window_reso.y);
  myRenderWindow.create(vm , "Game", sf::Style::Close);
}
