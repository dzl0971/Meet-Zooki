#include "Tile.h"


Tile::Tile()
{
	isFinish = false;
	isStart = false;
	isOccupied = false;
}

Tile::Tile(int posX, int posY, bool start, bool finish, TileSprite* t)
{
	window_x = posX;
	window_y = posY;
	isStart = start;
	isFinish = finish;
	tileSprite = t;
}


Tile::~Tile()
{
}

void Tile::setWindowPos(int x, int y, int tilesize)
{
	window_x = x * tilesize;
	window_y = y * tilesize;
}

void Tile::incrementNumberPlaced()
{
	tileSprite->incrementNumberPlaced();
}

void Tile::decrementNumberPlaced()
{
	tileSprite->decrementNumberPlaced();
}

TileSprite Tile::getTileSprite()
{
	return *tileSprite;
}

sf::Sprite Tile::getSprite()
{
	return tileSprite->getTileSprite();
}

int Tile::getWindowX()
{
	return window_x;
}

int Tile::getWindowY()
{
	return window_y;
}

bool Tile::maxPlaced()
{
	return tileSprite->maxPlaced();
}

bool Tile::isDrawn()
{
	return isOccupied;
}

int Tile::getID()
{
	return tileSprite->getID();
}

void Tile::Delete()
{
	
}
