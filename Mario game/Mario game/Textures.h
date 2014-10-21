//Player
sf::Texture mario_stay;
void player_textures(){
	   if(mario_stay.loadFromFile("Data/penguin.png")==false){
		   cout<<"Texture failed to initialize"<<endl;
	   }
}
sf::Texture mario_run1_d;
void player_textures1_d(){
	   //if(mario_run1_d.loadFromFile("Data/Mario_right_1.png")==false){
		if(mario_run1_d.loadFromFile("Data/penguin.png")==false){
		   cout<<"Texture failed to initialize"<<endl;
	   }
}
sf::Texture mario_run2_d;
void player_textures2_d(){
	   //if(mario_run2_d.loadFromFile("Data/Mario_right_2.png")==false){
		if(mario_run1_d.loadFromFile("Data/penguin.png")==false){
		   cout<<"Texture failed to initialize"<<endl;
	   }
}
sf::Texture mario_run3_d;
void player_textures3_d(){
	   //if(mario_run3_d.loadFromFile("Data/Mario_right_3.png")==false){
	if(mario_run1_d.loadFromFile("Data/penguin.png")==false){
		   cout<<"Texture failed to initialize"<<endl;
	   }
}
sf::Texture mario_run1_l;
void player_textures1_l(){
	  // if(mario_run1_l.loadFromFile("Data/Mario_left_1.png")==false){
	if(mario_run1_d.loadFromFile("Data/penguin.png")==false){
		   cout<<"Texture failed to initialize"<<endl;
	   }
}
sf::Texture mario_run2_l;
void player_textures2_l(){
	   //if(mario_run2_l.loadFromFile("Data/Mario_left_2.png")==false){
	if(mario_run1_d.loadFromFile("Data/penguin.png")==false){
		   cout<<"Texture failed to initialize"<<endl;
	   }
}
sf::Texture mario_run3_l;
void player_textures3_l(){
	   //if(mario_run3_l.loadFromFile("Data/Mario_left_3.png")==false){
	if(mario_run1_d.loadFromFile("Data/penguin.png")==false){
		   cout<<"Texture failed to initialize"<<endl;
	   }
}
sf::Texture mario_jump;
void player_jump(){
	if(mario_jump.loadFromFile("Data/penguin.png")==false){
		cout<<"Texture failed to initialize"<<endl;
	}
}

sf::Texture mario_down;
void player_down(){
	if(mario_down.loadFromFile("Data/penguin_down.png")==false){
		cout<<"Texture failed to initialize"<<endl;
	}
}

//Terrain
sf::Texture terrain_texture;
void terrain_textures(){
	  if(terrain_texture.loadFromFile("Data/Terrain.png")==false){
		  cout<<"Texture failed to initialize"<<endl;
	  }
}
//Background
sf::Texture background_texture;
void background_textures(){
	if(background_texture.loadFromFile("Data/mapsky.bmp")==false){
		cout<<"Texture failed to initialize"<<endl;
	}

}

//igloo
sf::Texture igloo_texture;
sf::Sprite igloo_sprite;
void igloo_textures(){
	if(igloo_texture.loadFromFile("Data/igloo.png")==false){
		cout<<"Texture failed to initialize"<<endl;
	}
	igloo_sprite.setTexture(igloo_texture);
	igloo_sprite.setPosition(745,485);

}