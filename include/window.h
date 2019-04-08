#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


const sf::Vector2u window_reso(640, 480);

class myWindowClass
{
    public:
        sf::RenderWindow myRenderWindow;
        myWindowClass(const std::string &);
        myWindowClass(); // default constructor
    private:
};

#endif
