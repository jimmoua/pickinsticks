#include "game.h"
#include <sstream>

namespace {
  static unsigned int playerScore;
  static sf::SoundBuffer loot;
  static sf::Sound soundLoot;
  static sf::Font scoreFont;
  static sf::Text scoreText;
  static sf::Music bgm;
}

// Handle character movement and event processing, update as needed
void game::update(playerClass   &myPlayerObject,
                  myWindowClass &myWindowObject,
                  map           &mapObject,
                  entityClass   &entityClassObject) 
{
  // Character speed
  float movespeed = 2.f;
  float spriteSize = 64.f;
  sf::Time t1 = myPlayerObject.animationClock.getElapsedTime();

  /* Because I've named them too long, I will use a ptr */
  const auto mO = &mapObject;
  const auto mPO = &myPlayerObject;
  const auto sS = spriteSize;

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
    movespeed+=3.f;
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    /* I have put these autos here because of how much of an idiot I was back
     * then naming variables insane long names. I am now suffering in order to
     * make them more readable. */
    auto yCol_1 = mO->mapView.getCenter().y;
    auto yCol_2 = mO->mapView.getSize().y/2;
    auto pPos_y = &(mPO->playerSprite.getPosition().y);
    auto mVCenter = &(mO->mapView.getCenter().y);
    if( yCol_1 > yCol_2 && pPos_y == mVCenter) {
      mO->mapView.move(0, -movespeed);
    }

    auto x = sf::IntRect(mPO->animationCounter*spriteSize, 0, 64, 64);
    mPO->playerSprite.setTextureRect(x);
    
    // Player Collision detection with the border
    auto yCol2 = *pPos_y - mPO->playerSprite.getTextureRect().height/2;
    if(yCol2 >= 0) {
      myPlayerObject.playerSprite.move(0, -movespeed);
    }
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    auto mapCenter_y = mapObject.mapView.getCenter().y;
    auto map_misc = mO->mapSprite.getTextureRect().height
      - mO->mapView.getSize().y/2;
    auto pPos_y = myPlayerObject.playerSprite.getPosition().y;

      if(mapCenter_y < map_misc && pPos_y == mapCenter_y) {
        mapObject.mapView.move(0, movespeed);
      }
      
      auto x = sf::IntRect(mPO->animationCounter*spriteSize, 128, 64, 64);
      myPlayerObject.playerSprite.setTextureRect(x);

      auto pRectH_2 = myPlayerObject.playerSprite.getTextureRect().height/2;
      auto mRectH = mapObject.mapSprite.getTextureRect().height;
      auto pRectH = myPlayerObject.playerSprite.getTextureRect().height;

      // Collision with bottom area of the map
      if(pPos_y - pRectH_2 <= mRectH - pRectH) {
        myPlayerObject.playerSprite.move(0, movespeed);
      }

  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    auto mCx = mapObject.mapView.getCenter().x;
    auto mVsX = mapObject.mapView.getSize().x/2;
    auto mPOSPx = myPlayerObject.playerSprite.getPosition().x;
    if(mCx > mVsX && mPOSPx == mCx) {
      mapObject.mapView.move(-movespeed, 0);
    }
    auto texRect = sf::IntRect(mPO->animationCounter*sS, sS, sS, sS);
    myPlayerObject.playerSprite.setTextureRect(texRect);
    auto pPosX = myPlayerObject.playerSprite.getPosition().x;
    auto pSTexR = myPlayerObject.playerSprite.getTextureRect().width/2;
    if(pPosX - pSTexR>= 0) {
      mPO->playerSprite.move(-movespeed, 0);
    }
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    auto mOmVCX = mapObject.mapView.getCenter().x;
    auto mSGTR = mapObject.mapSprite.getTextureRect().width
      - mapObject.mapView.getSize().x/2;
    auto iunno = mPO->playerSprite.getPosition().x==mO->mapView.getCenter().x;
      if( mOmVCX <  mSGTR && iunno) {
        mapObject.mapView.move(movespeed, 0);
      }
      auto fooRect = sf::IntRect(mPO->animationCounter*sS ,sS*3, sS, sS);
      myPlayerObject.playerSprite.setTextureRect(fooRect);

      auto baz = myPlayerObject.playerSprite.getPosition().x
        - myPlayerObject.playerSprite.getTextureRect().width/2;
      auto bar = mapObject.mapSprite.getTextureRect().width
        - myPlayerObject.playerSprite.getTextureRect().width;
      if(baz <= bar) {
        myPlayerObject.playerSprite.move(movespeed, 0);
      }
  }
  
  if(myPlayerObject.animationCounter >= 8) {
    myPlayerObject.animationCounter = 0;
  }

  if(t1 >= myPlayerObject.t) {
    myPlayerObject.animationCounter++;
    myPlayerObject.animationClock.restart();
  }
  // Center with the map
  // Each time the player move, the maps centers with it.
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
    entityClassObject.newPos(mapObject);
  }
  
  myWindowObject.myRenderWindow.setView(mapObject.mapView);

  // Checking for player interaction with stick
  auto psGB = entityClassObject.yeah.playerSprite.getGlobalBounds();
  if(myPlayerObject.playerSprite.getGlobalBounds().intersects(psGB)) {
    entityClassObject.newPos(mapObject);
    playLoot();
    playerScore++;
    updateScore();
    if(playerScore%3 == 0 && bgm.getPitch() < 1.f) {
      bgm.setPitch(bgm.getPitch()+.05);
    }
  } 
}

void game::init() {
  playerScore = 0;
  loot.loadFromFile("data/sound/itemLoot.wav");
  soundLoot.setBuffer(loot);
  soundLoot.setVolume(100);
  soundLoot.setPitch(1.5);
  bgm.openFromFile("data/sound/marble madness level 2.wav");
  bgm.setLoop(true);
  bgm.setVolume(20);
  bgm.setPitch(.50);
  bgm.play();
  scoreFont.loadFromFile("./data/Old School Adventures.ttf");
  scoreText.setFont(scoreFont);
  scoreText.setCharacterSize(32u); // font size to 32
  updateScore();
}

void game::playLoot() {
  soundLoot.play();
}

const sf::Text& game::getText() {
  return scoreText;
}

void game::updateScore() {
  std::ostringstream os;
  os << playerScore;
  std::string s = "Score: ";
  s.append(os.str());
  scoreText.setString(s);
}
