#include "game.h"
#include <sstream>

namespace {
  static unsigned int playerScore;
  static sf::SoundBuffer loot;
  static sf::Sound soundLoot;
  static sf::Font scoreFont;
  static sf::Text scoreText;
  static sf::Music bgm;

  // Load a map
  static map mo("./data/background.png");
  // Create stick
  static entityClass eo("./data/stick.png");
  // Create player
  static playerClass po("./data/character.png");
}

// Handle character movement and event processing, update as needed
void game::update() 
{
  // Character speed
  float movespeed = 2.f;
  float spriteSize = 64.f;
  sf::Time t1 = po.animationClock.getElapsedTime();

  /* Because I've named them too long, I will use a ptr */
  const auto sS = spriteSize;

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
    movespeed+=3.f;
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    /* I have put these autos here because of how much of an idiot I was back
     * then naming variables insane long names. I am now suffering in order to
     * make them more readable. */
    auto yCol_1 = mo.mapView.getCenter().y;
    auto yCol_2 = mo.mapView.getSize().y/2;
    auto pPos_y = &(po.playerSprite.getPosition().y);
    auto mVCenter = &(mo.mapView.getCenter().y);
    if( yCol_1 > yCol_2 && pPos_y == mVCenter) {
      mo.mapView.move(0, -movespeed);
    }

    auto x = sf::IntRect(po.animationCounter*spriteSize, 0, 64, 64);
    po.playerSprite.setTextureRect(x);
    
    // Player Collision detection with the border
    auto yCol2 = *pPos_y - po.playerSprite.getTextureRect().height/2;
    if(yCol2 >= 0) {
      po.playerSprite.move(0, -movespeed);
    }
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    auto mapCenter_y = mo.mapView.getCenter().y;
    auto map_misc = mo.mapSprite.getTextureRect().height
      - mo.mapView.getSize().y/2;
    auto pPos_y = po.playerSprite.getPosition().y;

      if(mapCenter_y < map_misc && pPos_y == mapCenter_y) {
        mo.mapView.move(0, movespeed);
      }
      
      auto x = sf::IntRect(po.animationCounter*spriteSize, 128, 64, 64);
      po.playerSprite.setTextureRect(x);

      auto pRectH_2 = po.playerSprite.getTextureRect().height/2;
      auto mRectH = mo.mapSprite.getTextureRect().height;
      auto pRectH = po.playerSprite.getTextureRect().height;

      // Collision with bottom area of the map
      if(pPos_y - pRectH_2 <= mRectH - pRectH) {
        po.playerSprite.move(0, movespeed);
      }

  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    auto mCx = mo.mapView.getCenter().x;
    auto mVsX = mo.mapView.getSize().x/2;
    auto mPOSPx = po.playerSprite.getPosition().x;
    if(mCx > mVsX && mPOSPx == mCx) {
      mo.mapView.move(-movespeed, 0);
    }
    auto texRect = sf::IntRect(po.animationCounter*sS, sS, sS, sS);
    po.playerSprite.setTextureRect(texRect);
    auto pPosX = po.playerSprite.getPosition().x;
    auto pSTexR = po.playerSprite.getTextureRect().width/2;
    if(pPosX - pSTexR>= 0) {
      po.playerSprite.move(-movespeed, 0);
    }
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    auto mOmVCX = mo.mapView.getCenter().x;
    auto mSGTR = mo.mapSprite.getTextureRect().width -
      mo.mapView.getSize().x/2;
    auto iunno = po.playerSprite.getPosition().x==mo.mapView.getCenter().x;
      if( mOmVCX <  mSGTR && iunno) {
        mo.mapView.move(movespeed, 0);
      }
      auto fooRect = sf::IntRect(po.animationCounter*sS ,sS*3, sS, sS);
      po.playerSprite.setTextureRect(fooRect);

      auto baz = po.playerSprite.getPosition().x
        - po.playerSprite.getTextureRect().width/2;
      auto bar = mo.mapSprite.getTextureRect().width
        - po.playerSprite.getTextureRect().width;
      if(baz <= bar) {
        po.playerSprite.move(movespeed, 0);
      }
  }
  
  if(po.animationCounter >= 8) {
    po.animationCounter = 0;
  }

  if(t1 >= po.t) {
    po.animationCounter++;
    po.animationClock.restart();
  }
  // Center with the map
  // Each time the player move, the maps centers with it.
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
    eo.newPos(mo);
  }
  
  game::window::getWindow()->setView(mo.mapView);

  // Checking for player interaction with stick
  auto psGB = eo.yeah.playerSprite.getGlobalBounds();
  if(po.playerSprite.getGlobalBounds().intersects(psGB)) {
    eo.newPos(mo);
    playLoot();
    playerScore++;
    updateScore();
    if(playerScore%3 == 0 && bgm.getPitch() < 1.f) {
      bgm.setPitch(bgm.getPitch()+.05);
    }
  } 
}

void game::init() {
  window::init();

  // Define starting position of player
  po.playerSprite.setPosition(mo.mapSprite.getTextureRect().width/2,
                              mo.mapSprite.getTextureRect().height/2);

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

void game::run() {
  while(window::getWindow()->isOpen())
  {
    static sf::Event e;
    while(window::getWindow()->pollEvent(e))
    {
      if(e.type == sf::Event::Closed) {
        window::getWindow()->close();
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
        window::getWindow()->close();
      }
    }
    window::getWindow()->clear(sf::Color::Black);
    window::getWindow()->draw(mo.mapSprite);
    window::getWindow()->draw(po.playerSprite);
    window::getWindow()->draw(eo.yeah.playerSprite);
    window::getWindow()->draw(game::getText());

    // handling movement and stuff
    update();

    window::getWindow()->display();
  }
}
