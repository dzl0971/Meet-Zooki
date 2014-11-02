#include <SFML/Graphics.hpp>
#include "editor.h"

int main()
{
	enum GameStates
	{
		Edit = 0,
		Test = 1,
	};

	GameStates state = Edit;
	Zooki zooki;

	int size_x = 1280;
	int size_y = 768;

	Editor edit(size_x / 32, size_y / 32);

	edit.LoadTiles("ZookieSpriteInfo.txt");

	sf::RenderWindow window(sf::VideoMode(size_x, size_y), "SFML works!");
	sf::Clock time;
	sf::Clock timeBetweenCommands;

	bool lastPressed = false;
	bool setStartPos = false; 
	float deltaTime;

	while (window.isOpen())
	{
		deltaTime = time.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				setStartPos = true;
			}
			else
			{
				setStartPos = false;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if (state == Edit)
				{
					int posX = sf::Mouse::getPosition(window).x;
					int posY = sf::Mouse::getPosition(window).y;

					if (posX >= 0 && posX <= size_x &&  posY >= 0 && posY <= size_y)
					{

						if (setStartPos)
						{
							posX = posX / 32;
							posY = posY / 32;
							zooki.setStart(posX, posY);
						}

						else if (!edit.getCurrentTile()->maxPlaced())
						{
							if (edit.getLevelTile(posX / 32, posY / 32)->getID() != -1 && edit.getLevelTile(posX / 32, posY / 32)->getID() != edit.getCurrentTile()->getID())
							{
								edit.getTile(edit.getLevelTile(posX / 32, posY / 32)->getID() - 1)->decrementNumberPlaced();
							}
							edit.setTileInLevel(*(edit.getCurrentTile()), posX / 32, posY / 32);
							edit.getCurrentTile()->incrementNumberPlaced();
						}
					}
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			{
				if (state == Edit)
				{
					int posX = sf::Mouse::getPosition(window).x;
					int posY = sf::Mouse::getPosition(window).y;

					if (posX >= 0 && posX <= size_x &&  posY >= 0 && posY <= size_y)
					{
						edit.removeTileInLevel(posX / 32, posY / 32);
						edit.getCurrentTile()->decrementNumberPlaced();
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (state == Edit)
				{
					if (!lastPressed && timeBetweenCommands.getElapsedTime().asMilliseconds() < 100)
					{
						continue;
					}
					lastPressed = false;
					edit.decrementCurrentTile();
					timeBetweenCommands.restart();
				}
				else if (state == Test)
				{
					zooki.moveLeft(deltaTime, 200);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (state == Edit)
				{
					if (lastPressed && timeBetweenCommands.getElapsedTime().asSeconds() < 100)
					{
						continue;
					}
					lastPressed = true;
					edit.incrementCurrentTile();
					timeBetweenCommands.restart();
				}
				else if (state == Test)
				{
					zooki.moveRight(deltaTime, 200);
				}

			}
			

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (state == Edit)
				{
					edit.SaveLevel();
				}
				else if (state == Test)
				{
					zooki.jump();
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				if (state == Edit)
				{
					edit.clearLevel();
				}
				
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				if (state == Edit)
				{
					edit.LoadLevel("level.txt");
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				if (timeBetweenCommands.getElapsedTime().asMilliseconds() > 100)
				{
					timeBetweenCommands.restart();
					if (state == Edit)
					{
						state = Test;
					}
					else if (state == Test)
					{
						zooki.resetPos();
						zooki.Update();
						state = Edit;
					}
				}
			}
		}

		zooki.Update();
		

		window.clear();
		window.draw(edit.getBackground());

		for (int i = 0; i < edit.getSizeX(); i++)
		{
			for (int j = 0; j < edit.getSizeY(); j++)
			{
				if (edit.getLevelTile(i, j)->getID() != -1){
					window.draw(edit.getLevelTile(i, j)->getTileSprite());
				}
			}
		}

		window.draw(zooki.getSprite());
		window.display();
	}

	return 0;
}
