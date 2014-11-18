#include "Tile.h"


Tile::Tile()
{
	ID = -1;
	numberPlaced = 0;
}

Tile::Tile(int id, std::string tileName)
{
	name = tileName;
	ID = id;
	numberPlaced = 0;
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

void Tile::setFinishData(int start, int finish)
{
	isStart = start;
	isFinish = finish;
}

void Tile::setWindowPos(int x, int y, int tilesize)
{
	window_x = x * tilesize;
	window_y = y * tilesize;
}

void Tile::setMaxNumber(int max)
{
	max_Number = max;
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

int Tile::getWindow_x()
{
	return window_x;
}

int Tile::getWindow_y()
{
	return window_y;
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

void Tile::incrementNumberPlaced()
{
	numberPlaced++;
}

void Tile::decrementNumberPlaced()
{
	numberPlaced--;
}

bool Tile::maxPlaced()
{
	if (max_Number == -1)  // infinite # of tiles can be placed
	{
		return false;
	}

	else
	{
		if (numberPlaced < max_Number)
		{
			return false;
		}
	}

	return true;
}

bool Tile::getIsStart()
{
	return isStart;
}
bool Tile::getIsFinish()
{
	return isFinish;
}

bool Tile::isDrawn()
{
	return isOccupied;
}

Tile::~Tile()
{
}
