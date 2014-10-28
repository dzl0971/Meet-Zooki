
sf::RectangleShape player;
void player_mesh(){	
player.setSize(sf::Vector2f(18,37));
player.setPosition(0,490);
player.setTexture(&mario_stay);
}
sf::RectangleShape terrain;
sf::Sprite background;
void background_mesh(){
	//background.setSize(sf::Vector2f(800,550));
    background.setPosition(0,0);
	background.setTexture(background_texture);
	background.setTextureRect(sf::IntRect(0,0,800,550));
}

 void terrain_mesh(){
	terrain.setSize(sf::Vector2f(800,76));
	terrain.setPosition(0,525);
	terrain.setTexture(&terrain_texture);
	
}