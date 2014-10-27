#include "TileSprite.h"


TileSprite::TileSprite()
{
	ID = -1;
	numberPlaced = 0;
}

TileSprite::TileSprite(int id)
{
	ID = id;
	numberPlaced = 0;
}

void TileSprite::setTileSprite(sf::Sprite sprite, int posX, int posY, int lenX, int lenY)
{
	tileSprite = sprite;
	x_pos = posX;
	y_pos = posY;
	x_len = lenX;
	y_len = lenY;
}

void TileSprite::setTileSpriteInfo(int L_Xoffset, int R_Xoffset, int L_Yoffset, int R_Yoffset)
{
	xOffset_L = L_Xoffset;
	xOffset_R = R_Xoffset;
	yOffset_L = L_Yoffset;
	yOffset_R = R_Yoffset;
	
}

void TileSprite::setTileSpriteInteraction(int solid, int deadly, int collectible)
{
	isSolid = solid;
	isDeadly = deadly;
	isCollectible = collectible;
}

void TileSprite::setFinishData(int start, int finish)
{
	isStart = start;
	isFinish = finish;
}

void TileSprite::setMaxNumber(int max)
{
	max_Number = max;
}

sf::Sprite TileSprite::getTileSprite()
{
	tileSprite.setPosition(sf::Vector2f(window_x, window_y));
	return tileSprite;
}

void TileSprite::Delete()
{
	decrementNumberPlaced();
}

int TileSprite::getID()
{
	return ID;
}

int TileSprite::getPosX()
{
	return x_pos;
}

int TileSprite::getPosY()
{
	return y_pos;
}

int TileSprite::getXOffset_L()
{
	return xOffset_L;
}

int TileSprite::getXOffset_R()
{
	return xOffset_R;
}

int TileSprite::getYOffset_L()
{
	return yOffset_L;
}

int TileSprite::getYOffset_R()
{
	return yOffset_R;
}

bool TileSprite::getIsSolid()
{
	return isSolid;
}

bool TileSprite::getIsDeadly()
{
	return isDeadly;
}

bool TileSprite::getIsCollectible()
{
	return isCollectible;
}

bool TileSprite::getIsStart()
{
	return isStart;
}
bool TileSprite::getIsFinish()
{
	return isFinish;
}

bool TileSprite::maxPlaced()
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

void TileSprite::incrementNumberPlaced()
{
	numberPlaced++;
}

void TileSprite::decrementNumberPlaced()
{
	numberPlaced--;
}

TileSprite::~TileSprite()
{
}
