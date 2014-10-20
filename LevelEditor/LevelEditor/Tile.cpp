#include "Tile.h"


Tile::Tile()
{
	ID = -1;
}

Tile::Tile(int id)
{
	ID = id;
}

void Tile::setTileSprite(sf::Sprite sprite, int posX, int posY, int lenX, int lenY)
{
	tileSprite = sprite;
	x_pos = posX;
	y_pos = posY;
	x_len = lenX;
	y_len = lenY;
}

void Tile::setTileInfo(int L_Xoffset, int R_Xoffset, int L_Yoffset, int R_Yoffset)
{
	xOffset_L = L_Xoffset;
	xOffset_R = R_Xoffset;
	yOffset_L = L_Yoffset;
	yOffset_R = R_Yoffset;
	
}

void Tile::setTileInteraction(int solid, int deadly, int collectible)
{
	isSolid = solid;
	isDeadly = deadly;
	isCollectible = collectible;
}

void Tile::setWindowPos(int x, int y, int tilesize)
{
	window_x = x * tilesize;
	window_y = y * tilesize;
}

sf::Sprite Tile::getTileSprite()
{
	tileSprite.setPosition(sf::Vector2f(window_x, window_y));
	return tileSprite;
}

void Tile::Delete()
{
	ID = -1;
}

int Tile::getID()
{
	return ID;
}

int Tile::getPosX()
{
	return x_pos;
}

int Tile::getPosY()
{
	return y_pos;
}

int Tile::getXOffset_L()
{
	return xOffset_L;
}

int Tile::getXOffset_R()
{
	return xOffset_R;
}

int Tile::getYOffset_L()
{
	return yOffset_L;
}

int Tile::getYOffset_R()
{
	return yOffset_R;
}

bool Tile::getIsSolid()
{
	return isSolid;
}

bool Tile::getIsDeadly()
{
	return isDeadly;
}

bool Tile::getIsCollectible()
{
	return isCollectible;
}

Tile::~Tile()
{
}
