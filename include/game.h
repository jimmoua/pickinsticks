#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "window.h"
#include "map.h"
#include "character.h"
#include <SFML/Audio.hpp>
class game
{
    public:
        void update(playerClass &, myWindowClass &, map &, entityClass &);
        game();
        ~game();
        sf::Music bgm;
        void playLoot();
        sf::Text getText();
        void updateScore();
    private:
        unsigned int playerScore;
        sf::SoundBuffer loot;
        sf::Sound soundLoot;
        sf::Font scoreFont;
        sf::Text scoreText;
};


