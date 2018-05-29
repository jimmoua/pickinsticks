#include "window.h"


myWindowClass::myWindowClass(const std::string &titleName)
{
    myRenderWindow.create(sf::VideoMode(window_reso.x, window_reso.y), titleName, sf::Style::Close);
    myRenderWindow.setFramerateLimit(60);
}

myWindowClass::myWindowClass()
{
    // default ctr
    myRenderWindow.create(sf::VideoMode(window_reso.x, window_reso.y), "Game", sf::Style::Close);
}
