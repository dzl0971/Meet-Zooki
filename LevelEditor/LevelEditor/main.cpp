#include <SFML/Graphics.hpp>
#include "editor.h"
#include "Zooki.h"

int main()
{
	
	enum Gamestates
	{
		Editing = 0,
		Testing = 1,
		Saving = 2
	};

	Gamestates state = Editing;

	const int size_x = 1280;
	const int size_y = 768;
	const int runSpeed = 200;
	const int gravity = 200;

	Editor edit(size_x/32, size_y/32);

	edit.LoadTiles();

	sf::RenderWindow window(sf::VideoMode(size_x, size_y), "Zooki Level Editor");
	sf::Clock clock;
	
	bool lastPressed = false;
	float deltaTime = 0;

	Zooki zooki;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			
			if (state == Testing)
			{
				float deltaTime = clock.restart().asSeconds();
			}

			if (event.type == sf::Event::Closed)
				window.close();
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if (state == Editing) {
					int posX = sf::Mouse::getPosition(window).x;
					int posY = sf::Mouse::getPosition(window).y;

					if (posX >= 0 && posX <= size_x &&  posY >= 0 && posY <= size_y)
					{
						edit.setTileInLevel(edit.getCurrentTile(), posX / 32, posY / 32);
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			{
				if (state == Editing)
				{
					int posX = sf::Mouse::getPosition(window).x;
					int posY = sf::Mouse::getPosition(window).y;

					if (posX >= 0 && posX <= size_x &&  posY >= 0 && posY <= size_y)
					{
						edit.removeTileInLevel(posX / 32, posY / 32);
					}
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (state == Editing)
				{
					if (!lastPressed && clock.getElapsedTime().asMilliseconds() < 10)
					{
						continue;
					}
					lastPressed = false;
					edit.decrementCurrentTile();
					clock.restart();
				}

				else if (state == Testing)
				{
					zooki.moveLeft(deltaTime, runSpeed);
				}

			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (state == Editing)
				{
					if (lastPressed && clock.getElapsedTime().asMilliseconds() < 10)
					{
						continue;
					}
					lastPressed = true;
					edit.incrementCurrentTile();
					clock.restart();
				}

				else if (state == Testing)
				{
					zooki.moveRight(deltaTime, runSpeed);
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (state == Testing)
				{
					zooki.jump();
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (state == Testing)
				{
					zooki.slide();
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (state == Editing)
				{
					edit.SaveLevel();
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				if (state == Editing)
				{
					edit.clearLevel();
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				if (state == Editing)
				{
					state = Testing;
				}

				else if (state == Testing)
				{
					state == Editing;
				}

			}
			
		}

		
		window.clear();
		window.draw(edit.getBackground());
		
		for (int i = 0; i < edit.getSizeX(); i++)
		{
			for (int j = 0; j < edit.getSizeY(); j++)
			{
				if (edit.getLevelTile(i,j).isDrawn()){

					edit.getLevelTile(i, j).getSprite().setPosition(edit.getLevelTile(i, j).getWindowX(), edit.getLevelTile(i, j).getWindowY());
					window.draw(edit.getLevelTile(i, j).getSprite());
				}
			}
		}
		
		//window.draw(sprite);
		window.display();
	}

	return 0;
}
