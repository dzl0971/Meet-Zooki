#include "editor.h"

Editor::Editor()
{
	// 1280 x 928 
	level.resize(40);
	for (int i = 0; i < 40; i++)
	{
		level[i].resize(29);
	}
	size_x = 40;
	size_y = 29;
	tileSize = 32;
	currentTile = 0;
	background.loadFromFile("Data/background.png");
	backgroundSprite.setTexture(background);
	backgroundSprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
	backgroundSprite.setScale(sf::Vector2f(2, 2));
}

Editor::Editor(int x, int y, int tilesize)
{
	// (X*tilesize) x Y*tilesize) 
	level.resize(x);
	for (int i = 0; i < x; i++)
	{
		level[i].resize(y);
	}
	size_x = x;
	size_y = y;
	tileSize = tilesize;
	currentTile = 0;
	background.loadFromFile("Data/background.png");
	backgroundSprite.setTexture(background);
	backgroundSprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
	backgroundSprite.setScale(sf::Vector2f(2, 2));
}

Editor::Editor(std::string filename, int sizeX, int sizeY)
{
	LoadLevel(filename);
	
	
	background.loadFromFile("Data/background.png");
	backgroundSprite.setTexture(background);
	backgroundSprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
	backgroundSprite.setScale(sf::Vector2f(2, 2));
	
}

Tile* Editor::getTile(int x)
{
	return &tiles.at(x);
}

sf::Sprite Editor::getBackground()
{
	return backgroundSprite;
}

Tile* Editor::getCurrentTile()
{
	return &tiles.at(currentTile);
}

Tile* Editor::getLevelTile(int x, int y)
{
	level[x][y].setWindowPos(x, y, tileSize);
	return &level[x][y];
}

int Editor::getSizeX()
{
	return size_x;
}

int Editor::getSizeY()
{
	return size_y;
}

int Editor::getStartX()
{
	return startX;
}

int Editor::getStartY()
{
	return startY;
}

void Editor::setStart(int x, int y)
{
	startX = x;
	startY = y;
}

std::vector<std::vector<Tile>> Editor::getLevel()
{
	return level;
}

std::vector<Tile> Editor::getAllTiles()
{
	return tiles;
}

void Editor::setTileInLevel(Tile t, int x, int y)
{
	level[x][y] = t;
}

void Editor::removeTileInLevel(int x, int y)
{
	level[x][y].Delete();
}

void Editor::clearLevel()
{
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			level[i][j].Delete();
		}
	}
}

void Editor::incrementCurrentTile()
{
	currentTile++;
	if (currentTile < tiles.size())
	{
		if (getTile(currentTile)->getTileSprite().getTexture() == NULL)
		{
			incrementCurrentTile();
		}
	}
	else
	{
		currentTile = 0;
		if (getTile(currentTile)->getTileSprite().getTexture() == NULL)
		{
			incrementCurrentTile();
		}
	}
}

void Editor::decrementCurrentTile()
{

	currentTile--;
	if (currentTile > 0)
	{
		if (getTile(currentTile)->getTileSprite().getTexture() == NULL)
		{
			decrementCurrentTile();
		}
	}
	else
	{
		currentTile = tiles.size() - 1;
		if (getTile(currentTile)->getTileSprite().getTexture() == NULL)
		{
			decrementCurrentTile();
		}
	}
}

// creates a vector of tiles for use in the game
void Editor::LoadTiles(std::string filename)
{
	std::filebuf infoFile;
	spriteInfoSheetName = filename;

	if (infoFile.open(filename.c_str(), std::ios::in))
	{
		std::istream stream(&infoFile);

		std::getline(stream, spriteSheetName);
		LoadSpriteSheet(spriteSheetName);

		//add in background

		std::string temp; // tempX used to fill in Tile objects
		std::string temp2;
		std::string temp3;
		std::string temp4;

		while (stream)
		{
			
			std::getline(stream, temp); //name
			if (temp == "+--+")
			{
				break;
			}
			std::getline(stream, temp2); //ID

			Tile t(convertStringToInt(temp2),temp);

			std::getline(stream, temp); //xpos
			std::getline(stream, temp2); //ypos
			std::getline(stream, temp3); //xlen
			std::getline(stream, temp4); //ylen

			int xpos = convertStringToInt(temp);
			int ypos = convertStringToInt(temp2);
			int lenx = convertStringToInt(temp3);
			int leny = convertStringToInt(temp4);

			getSpriteFromFile(t, xpos, ypos, lenx, leny);
			sf::Sprite sprite;
			sprite.setTexture(spriteSheet);
			sprite.setTextureRect(sf::IntRect(xpos, ypos, lenx, leny));
			sprite.scale(sf::Vector2f(.5, .5));
			t.setTileSprite(sprite, xpos, ypos, lenx, leny);

			std::getline(stream, temp); // max_num
			t.setMaxNumber(convertStringToInt(temp));

			std::getline(stream, temp); //xoffL
			std::getline(stream, temp2); //xoffR
			std::getline(stream, temp3); //yoffL
			std::getline(stream, temp4); //yoffR

			t.setTileInfo(convertStringToInt(temp), convertStringToInt(temp2), convertStringToInt(temp3), convertStringToInt(temp4));

			std::getline(stream, temp); //isSolid
			std::getline(stream, temp2); //isdeadly
			std::getline(stream, temp3); //iscollectible

			t.setTileInteraction(convertStringToInt(temp), convertStringToInt(temp2), convertStringToInt(temp3));

			std::getline(stream, temp); //isStart
			std::getline(stream, temp2); //isFinish

			t.setFinishData(convertStringToInt(temp), convertStringToInt(temp2));

			tiles.push_back(t);
		}

		infoFile.close();
	}
}

void Editor::LoadLevel(std::string filename)
{
	std::string temp;
	int tempID;
	int tempX;
	int tempY;

	std::ifstream levelFile(filename.c_str());

	std::getline(levelFile, spriteInfoSheetName);
	if (tiles.size() == 0)
	{
		LoadTiles(filename);
	}

	for (int i = 0; i < size_x; i++)
	{
		level[i].clear();
	}

	std::getline(levelFile, temp);
	size_x = convertStringToInt(temp);

	std::getline(levelFile, temp);
	size_y = convertStringToInt(temp);
	std::getline(levelFile, temp);
	tileSize = convertStringToInt(temp);

	

	level.resize(size_x);
	for (int i = 0; i < size_x; i++)
	{
		level[i].resize(size_y);
	}

	std::getline(levelFile, temp);
	startX = convertStringToInt(temp);
	std::getline(levelFile, temp);
	startY = convertStringToInt(temp);

	while (levelFile)
	{
		std::getline(levelFile, temp);
		if (temp == "+--+")
		{
			break;
		}

		tempID = convertStringToInt(temp);

		std::getline(levelFile, temp);
		tempX = convertStringToInt(temp);
		std::getline(levelFile, temp);
		tempY = convertStringToInt(temp);

		setTileInLevel(tiles[tempID - 1], tempX, tempY);
	}

	levelFile.close();
}

void Editor::SaveLevel()
{
	std::ofstream levelData;
	levelData.open("level.txt");

	levelData << spriteInfoSheetName;
	levelData << "\n";
	levelData << size_x;
	levelData << "\n";
	levelData << size_y;
	levelData << "\n";
	levelData << tileSize;
	levelData << "\n";
	levelData << startX;
	levelData << "\n";
	levelData << startY;
	levelData << "\n";

	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			if (level[i][j].getID() != -1 && level[i][j].getTileSprite().getTexture() != NULL)
			{
				levelData << level[i][j].getID();
				levelData << "\n";
				levelData << i;
				levelData << "\n";
				levelData << j;
				levelData << "\n";
			}
		}
	}
	levelData << "+--+";

	levelData.close();
}

// load  texture from file
void Editor::LoadSpriteSheet(std::string filename)
{
	spriteSheet.loadFromFile(filename);
}

// create sprites from spritesheet
void Editor::getSpriteFromFile(Tile t, int posx, int posy, int lenx, int leny)
{
	t.getTileSprite().setTexture(spriteSheet);

}

//converts a string to an int
int Editor::convertStringToInt(std::string s)
{
	int i;
	std::istringstream(s) >> i;
	return i;
}

Editor::~Editor()
{
}
