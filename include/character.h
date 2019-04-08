#pragma once
#include <SFML/Graphics.hpp>
#include "map.h"
class playerClass // I should have made a pure virtual functoin class and let player and entity inherit from it, but oh well too late
{
    public:
        sf::Texture playerTexture;
        sf::Sprite playerSprite;
        playerClass(const std::string &);
        playerClass(); // default ctor
        unsigned short int animationCounter = 0;
        sf::Clock animationClock;
        const sf::Time t = sf::seconds(.15);
};

class entityClass
{
    public:
        sf::Vector2f seed;
        void newPos(map &mapClassObject);
        entityClass(const std::string &);
        entityClass();
        playerClass yeah;
    private:
};


