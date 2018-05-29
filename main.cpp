#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "game.h"
int main()
{
    map mapObject("./data/background.png");
    game engine; // Game class object
    myWindowClass myObject("Game");
    playerClass myPlayerObject("./data/character.png"); // Loaded the character from file
    myObject.myRenderWindow.setView(mapObject.mapView); // Set the inital map view to the middle of the map.
    myPlayerObject.playerSprite.setPosition(mapObject.mapView.getCenter().x, mapObject.mapView.getCenter().y); // Set the position of the sprite
    entityClass entityClassObject("./data/stick.png");
    while(myObject.myRenderWindow.isOpen()) // Main loop
    {
        myObject.myRenderWindow.clear(sf::Color::Black);
        sf::Event myEvent;
        while(myObject.myRenderWindow.pollEvent(myEvent))
        {
            if(myEvent.type == sf::Event::Closed)
                myObject.myRenderWindow.close();
        }
        
        // Draw
        engine.update(myPlayerObject, myObject, mapObject, entityClassObject);
        myObject.myRenderWindow.draw(mapObject.mapSprite); // Draw the map
        myObject.myRenderWindow.draw(myPlayerObject.playerSprite); // Draw the sprite
        myObject.myRenderWindow.draw(entityClassObject.yeah.playerSprite); // Draw the stick
        myObject.myRenderWindow.draw(engine.getText());
        myObject.myRenderWindow.display();
    }
    return 0;
}
