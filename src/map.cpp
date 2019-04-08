#include "map.h"



map::map(const std::string &pathToMap)
{
    this->mapTexture.loadFromFile(pathToMap);
    this->mapSprite.setTexture(this->mapTexture);
    mapSprite.setTexture(map::mapTexture);
    mapView.setSize(window_reso.x, window_reso.y);
    mapView.setCenter(mapSprite.getTextureRect().width/2, mapSprite.getTextureRect().height/2);
}

map::map()
{
    // Default
}

map::~map()
{
    // Not defined yet
}


