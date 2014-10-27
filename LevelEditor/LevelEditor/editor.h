#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<SFML/Graphics.hpp>
#include "Tile.h"
#include "TileSprite.h"

class Editor
{
public:
	Editor();
	Editor(int x, int y);
	Editor(std::string levelFile);
	~Editor();

	void LoadTiles();
	void LoadLevel();
	void SaveLevel();

	//TODO setPlayerSprite
	void setBackground(std::string filename); // load the background
	void setTileSet(std::string filename, std::string tileInfo); // load tiles being used in level
	void setPlayerSprite(std::string filename, std::string spriteInfo);
	void setTileInLevel(TileSprite t, int x, int y); // place tile in level array
	void removeTileInLevel(int x, int y); // remove tile from level array
	void clearLevel();
		
	void incrementCurrentTile(); // curTile++
	void decrementCurrentTile(); // curTile--
	
	sf::Sprite getBackground(); // get background texture
	std::vector < std::vector<Tile>> getLevel(); // return level array

	Tile getLevelTile(int x, int y); // get tile pointer from level array
	TileSprite getTile(int x); // get tile from sprite array
	TileSprite getCurrentTile(); // get current tile selected

	int getSizeX();
	int getSizeY();

	sf::Sprite* getplayerSprite();
	
private:
	sf::Texture background;
	sf::Texture spriteSheet; // sprite sheet texture
	std::vector<TileSprite> tiles; // array of tiles loaded from sprite sheet
	sf::Sprite playerSprite; // player sprite
	sf::Sprite backgroundSprite;

	std::string spriteSheetName;

	std::vector<std::vector<Tile>> level; // 2d level array

	int size_x; // x size of level array
	int size_y; // y size of level array
	int tileSize; // how big are tiles (assume size x = size y)
	int startX; // x position of start
	int startY; // y position of start
	int finishX; // x position of finish
	int finishY; // y position of finish

	int currentTile; // current tile being placed

	void LoadSpriteSheet(std::string filename);
	void LoadBackground(std::string filename);
	void getSpriteFromFile(TileSprite t, int posx, int posy, int lenx, int leny);
	int convertStringToInt(std::string s);

};

