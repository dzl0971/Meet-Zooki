#include <SFML/Graphics.hpp>
#include "editor.h"

int main()
{
	

	int size_x = 1280;
	int size_y = 768;

	Editor edit(1280/32, 768/32);

	edit.LoadTiles();

	sf::RenderWindow window(sf::VideoMode(size_x, size_y), "SFML works!");
	sf::Clock time;
	
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(32, 32));
	sf::RectangleShape shape2;
	shape2.setSize(sf::Vector2f(32, 96));

	/*edit.setTileInLevel(edit.getTile(1), 0, 1);
	edit.setTileInLevel(edit.getTile(1), 0, 3);
	edit.setTileInLevel(edit.getTile(1), 39, 20);
	edit.setTileInLevel(edit.getTile(1), 0, 0);*/

	shape2.setFillColor(sf::Color::Green);
	shape.setFillColor(sf::Color::Red);

	bool lastPressed = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				int posX = sf::Mouse::getPosition(window).x;
				int posY = sf::Mouse::getPosition(window).y;

				if (posX >= 0 && posX <= size_x &&  posY >= 0 && posY <= size_y)
				{
					edit.setTileInLevel(edit.getCurrentTile(), posX / 32, posY / 32);
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			{
				int posX = sf::Mouse::getPosition(window).x;
				int posY = sf::Mouse::getPosition(window).y;

				if (posX >= 0 && posX <= size_x &&  posY >= 0 && posY <= size_y)
				{
					edit.removeTileInLevel(posX/ 32, posY / 32);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (!lastPressed && time.getElapsedTime().asMilliseconds() < 10)
				{
					continue;
				}
				lastPressed = false;
				edit.decrementCurrentTile();
				time.restart();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (lastPressed && time.getElapsedTime().asMilliseconds() < 10)
				{
					continue;
				}
				lastPressed = true;
				edit.incrementCurrentTile();
				time.restart();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				
				edit.SaveLevel();
			}
		}

		
		window.clear();

		for (int i = 0; i < edit.getSizeX(); i++)
		{
			for (int j = 0; j < edit.getSizeY(); j++)
			{
				if (edit.getLevelTile(i,j).getID() != -1){
					window.draw(edit.getLevelTile(i, j).getTileSprite());
				}
			}
		}
		
		//window.draw(sprite);
		window.display();
	}

	return 0;
}
