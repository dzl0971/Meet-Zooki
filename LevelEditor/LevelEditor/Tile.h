#pragma once
#include "TileSprite.h"

class Tile
{
public:
	Tile();
	Tile(int posX, int posY, bool start, bool finish, TileSprite* t);

	~Tile();

	void setWindowPos(int x, int y, int tilesize);
	void incrementNumberPlaced();
	void decrementNumberPlaced();

	TileSprite getTileSprite();
	sf::Sprite getSprite();
	int getWindowX();
	int getWindowY();

	bool maxPlaced(); // has the maximum number of tiles been placed
	bool isDrawn(); // whether or not this tile is drawn on the screen

	int getID();

	void Delete();

private:
	TileSprite* tileSprite;

	int window_x;
	int window_y;
	bool isStart;
	bool isFinish;
	bool isOccupied;

};

