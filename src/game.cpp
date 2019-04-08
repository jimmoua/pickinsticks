#include "game.h"
#include <sstream>

void game::update(playerClass &myPlayerObject, myWindowClass &myWindowObject, map &mapObject, entityClass &entityClassObject) // This is mainly movement handling and stick event proccessing
{
    // Update funciton
    float movespeed = 2.f;
    float spriteSize = 64.f;
    sf::Time t1 = myPlayerObject.animationClock.getElapsedTime();
    // Could probably work on the readability of the lines in the future...
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
    {
        movespeed+=2.f;

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if(mapObject.mapView.getCenter().y > mapObject.mapView.getSize().y/2 and myPlayerObject.playerSprite.getPosition().y==mapObject.mapView.getCenter().y) // Checks for map view collision going out of view with map boundaries
            mapObject.mapView.move(0, -movespeed);
        myPlayerObject.playerSprite.setTextureRect(sf::IntRect(myPlayerObject.animationCounter*spriteSize, 0, 64, 64));
        if(myPlayerObject.playerSprite.getPosition().y-myPlayerObject.playerSprite.getTextureRect().height/2  >= 0) // Player Collision detection with the map.
            myPlayerObject.playerSprite.move(0, -movespeed);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if(mapObject.mapView.getCenter().y < mapObject.mapSprite.getTextureRect().height-mapObject.mapView.getSize().y/2 and myPlayerObject.playerSprite.getPosition().y==mapObject.mapView.getCenter().y)
            mapObject.mapView.move(0, movespeed);
        myPlayerObject.playerSprite.setTextureRect(sf::IntRect(myPlayerObject.animationCounter*spriteSize, 128, 64, 64));
        if(myPlayerObject.playerSprite.getPosition().y-myPlayerObject.playerSprite.getTextureRect().height/2 <= mapObject.mapSprite.getTextureRect().height - myPlayerObject.playerSprite.getTextureRect().height) // Collision with bottom area of the map
            myPlayerObject.playerSprite.move(0, movespeed);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if(mapObject.mapView.getCenter().x > mapObject.mapView.getSize().x/2 and myPlayerObject.playerSprite.getPosition().x==mapObject.mapView.getCenter().x)
            mapObject.mapView.move(-movespeed, 0);
        myPlayerObject.playerSprite.setTextureRect(sf::IntRect(myPlayerObject.animationCounter*spriteSize, spriteSize, spriteSize, spriteSize));
        if(myPlayerObject.playerSprite.getPosition().x-myPlayerObject.playerSprite.getTextureRect().width/2 >= 0)
            myPlayerObject.playerSprite.move(-movespeed, 0);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if(mapObject.mapView.getCenter().x < mapObject.mapSprite.getTextureRect().width-mapObject.mapView.getSize().x/2 and myPlayerObject.playerSprite.getPosition().x==mapObject.mapView.getCenter().x)
            mapObject.mapView.move(movespeed, 0);
        myPlayerObject.playerSprite.setTextureRect(sf::IntRect(myPlayerObject.animationCounter*spriteSize ,spriteSize*3, spriteSize, spriteSize));
        if(myPlayerObject.playerSprite.getPosition().x-myPlayerObject.playerSprite.getTextureRect().width/2 <= mapObject.mapSprite.getTextureRect().width - myPlayerObject.playerSprite.getTextureRect().width)
        myPlayerObject.playerSprite.move(movespeed, 0);
    }
    
    if(myPlayerObject.animationCounter >= 8)
        myPlayerObject.animationCounter = 0;

    if(t1 >= myPlayerObject.t)
    {
        myPlayerObject.animationCounter++;
        myPlayerObject.animationClock.restart();
    }
    // Center with the map
    // Each time the player move, the maps centers with it.
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
        entityClassObject.newPos(mapObject);
    
    myWindowObject.myRenderWindow.setView(mapObject.mapView);

    // Checking for player interaction with stick
    if(myPlayerObject.playerSprite.getGlobalBounds().intersects(entityClassObject.yeah.playerSprite.getGlobalBounds()))
    {
        entityClassObject.newPos(mapObject);
        playLoot();
        playerScore++;
        updateScore();
    } 
}

game::game() // default constructor
{
    playerScore = 0;
    loot.loadFromFile("../../sounds/itemLoot.wav");
    soundLoot.setBuffer(loot);
    soundLoot.setVolume(201);
    bgm.openFromFile("./data/sound/Marble Madness (NES) Music - Level 2 Theme.wav");
    bgm.setLoop(true);
    bgm.play();
    scoreFont.loadFromFile("./data/Old School Adventures.ttf");
    scoreText.setFont(scoreFont);
    scoreText.setCharacterSize(32u); // font size to 32
    updateScore();
}
game::~game()
{
    //default dtor
}

void game::playLoot()
{
    soundLoot.play();
}

sf::Text game::getText()
{
    return scoreText;
}

void game::updateScore()
{
    std::ostringstream os;
    os << playerScore;
    std::string s = "Score: ";
    s.append(os.str());
    scoreText.setString(s);
}
