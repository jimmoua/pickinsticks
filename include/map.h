#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "window.h"


class map
{
    public:
        sf::View mapView;
        sf::Sprite mapSprite;
        sf::Texture mapTexture;
        map(const std::string &);
        ~map();
        map();

};

