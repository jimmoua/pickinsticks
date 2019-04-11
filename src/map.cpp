#include "map.h"



map::map(const std::string &pathToMap) {
  this->mapTexture.loadFromFile(pathToMap);
  this->mapSprite.setTexture(this->mapTexture);
  mapSprite.setTexture(map::mapTexture);
  mapView.setSize(game::window::gwinResX(), game::window::gwinResY());
  auto newCenter_w = mapSprite.getTextureRect().width/2;
  auto newCenter_h = mapSprite.getTextureRect().height/2;
  mapView.setCenter(newCenter_w, newCenter_h);
}

map::map() { }

map::~map() { }
