#include "game.h"
#include "window.h"
#include "character.h"
#include "map.h"

int main()
{
    map mapClassObject("./data/background.png");
    entityClass entityClassObject("./data/stick.png");
    playerClass playerClassObject("./data/character.png");
    game engine;
    myWindowClass windowClassObject("Pickin' Sticks");

    // I did not set the starting position of the character inside the class, so
    // I will do it inside main.
    playerClassObject.playerSprite.setPosition(mapClassObject.mapSprite.getTextureRect().width/2, mapClassObject.mapSprite.getTextureRect().height/2);
    while(windowClassObject.myRenderWindow.isOpen())
    {
        sf::Event e;
        while(windowClassObject.myRenderWindow.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
                windowClassObject.myRenderWindow.close();
        }
        windowClassObject.myRenderWindow.draw(mapClassObject.mapSprite);
        windowClassObject.myRenderWindow.draw(playerClassObject.playerSprite);
        windowClassObject.myRenderWindow.draw(entityClassObject.yeah.playerSprite);
        windowClassObject.myRenderWindow.draw(engine.getText());
        engine.update(playerClassObject, windowClassObject, mapClassObject, entityClassObject); // handling movement and stuff

        windowClassObject.myRenderWindow.display();
    }


    return 0;
}
