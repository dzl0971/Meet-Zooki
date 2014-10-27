#pragma once
#include<SFML/Graphics.hpp>

class TileSprite
{
public:
	TileSprite();
	TileSprite(int id);
	~TileSprite();

	
	void setTileSprite(sf::Sprite sprite, int posX, int posY, int lenX, int lenY); // set the sprite
	void setMaxNumber(int max); //sets the max number of sprites allowed
	void setTileSpriteInfo(int L_Xoffset, int R_Xoffset, int L_Yoffset, int R_Yoffset); // set tile data
	void setTileSpriteInteraction(int solid, int deadly, int collectible);// set tile interaction data
	void setFinishData(int start, int finish);

	void setWindowPos(int x, int y, int tilesize);
	
	sf::Sprite getTileSprite();

	int getID();
	int getPosX();
	int getPosY();
	int getXOffset_L();
	int getXOffset_R();
	int getYOffset_L();
	int getYOffset_R();

	bool getIsSolid();
	bool getIsDeadly();
	bool getIsCollectible();
	bool getIsStart();
	bool getIsFinish();

	bool maxPlaced(); // has the maximum number of tiles been placed
	
	void incrementNumberPlaced();
	void decrementNumberPlaced();

	void Delete();

private:

	sf::Sprite tileSprite;
	int ID; // ID of sprite

	int x_pos; // x position of sprite in sprite sheet
	int y_pos; // y position of sprite in sprite sheet
	int x_len; // x length of sprite in sprite sheet
	int y_len; // y length of sprite in sprite sheet
	int max_Number; // how many of these tiles can be placed

	int window_x; // x pos in window
	int window_y; // y os in window

	int xOffset_L; // distance sprite is from left of tile
	int xOffset_R; // distance sprite is from right of tile
	int yOffset_L; // distance from top of tile to first pixel of left edge.  used for slope
	int yOffset_R; // distance from top of tile to first pixel of left edge.  used for slope

	bool isSolid; // can player walk on tile
	bool isDeadly; // does tile make you lose a life
	bool isCollectible; // should item disappear if player enters tile
	bool isStart;
	bool isFinish;

	int numberPlaced; //number of this tile placed

};

